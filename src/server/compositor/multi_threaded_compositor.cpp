/*
 * Copyright © 2013-2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#include "multi_threaded_compositor.h"
#include "mir/graphics/display.h"
#include "mir/graphics/display_buffer.h"
#include "mir/graphics/cursor.h"
#include "mir/compositor/display_buffer_compositor.h"
#include "mir/compositor/display_buffer_compositor_factory.h"
#include "mir/compositor/scene.h"
#include "mir/compositor/compositor_report.h"
#include "mir/scene/legacy_scene_change_notification.h"
#include "mir/scene/surface_observer.h"
#include "mir/scene/surface.h"
#include "mir/run_mir.h"
#include "mir/thread_name.h"

#include <thread>
#include <condition_variable>

namespace mc = mir::compositor;
namespace mg = mir::graphics;
namespace ms = mir::scene;

namespace
{

class ApplyIfUnwinding
{
public:
    ApplyIfUnwinding(std::function<void()> const& apply)
        : apply{apply}
    {
    }

    ~ApplyIfUnwinding()
    {
        if (std::uncaught_exception())
            apply();
    }

private:
    ApplyIfUnwinding(ApplyIfUnwinding const&) = delete;
    ApplyIfUnwinding& operator=(ApplyIfUnwinding const&) = delete;

    std::function<void()> const apply;
};

}

namespace mir
{
namespace compositor
{

/**
 * MultiCursor is the top-level cursor implementation providing a single
 * cursor instance to the display server, but is able to multiplex all
 * cursor calls to multiple (per-display) visible cursors.
 */
class MultiCursor : public graphics::Cursor
{
public:
    MultiCursor(MultiThreadedCompositor& compositor)
        : compositor(compositor)
    {
    }

    void show(mg::CursorImage const&) override
    {
        // Maybe later if we want to implement software-rendered cursors
    }

    void hide() override
    {
    }

    void move_to(geometry::Point position) override
    {
        compositor.on_cursor_movement(position);
    }

private:
    MultiThreadedCompositor& compositor;
};

class CurrentRenderingTarget
{
public:
    CurrentRenderingTarget(mg::DisplayBuffer& buffer)
        : buffer(buffer)
    {
        buffer.make_current();
    }

    ~CurrentRenderingTarget()
    {
        buffer.release_current();
    }

private:
    mg::DisplayBuffer& buffer;
};

class CompositingFunctor
{
public:
    CompositingFunctor(std::shared_ptr<mc::DisplayBufferCompositorFactory> const& db_compositor_factory,
                       mg::DisplayBuffer& buffer,
                       std::shared_ptr<CompositorReport> const& report)
        : display_buffer_compositor_factory{db_compositor_factory},
          buffer(buffer),
          running{true},
          frames_scheduled{0},
          report{report},
          zoom_mag{0.0f}
    {
    }

    void operator()() noexcept  // noexcept is important! (LP: #1237332)
    try
    {
        mir::set_thread_name("Mir/Comp");

        /*
         * Make the buffer the current rendering target, and release
         * it when the thread is finished.
         */
        CurrentRenderingTarget target{buffer};

        display_buffer_compositor = display_buffer_compositor_factory->create_compositor_for(buffer);

        CompositorReport::SubCompositorId report_id =
            display_buffer_compositor.get();

        const auto& r = buffer.view_area();
        report->added_display(r.size.width.as_int(), r.size.height.as_int(),
                              r.top_left.x.as_int(), r.top_left.y.as_int(),
                              report_id);

        std::unique_lock<std::mutex> lock{run_mutex};
        while (running)
        {
            /* Wait until compositing has been scheduled or we are stopped */
            run_cv.wait(lock, [&]{ return (frames_scheduled > 0) || !running; });

            /*
             * Check if we are running before compositing, since we may have
             * been stopped while waiting for the run_cv above.
             */
            if (running)
            {
                /*
                 * Each surface could have a number of frames ready in its buffer
                 * queue. And we need to ensure that we render all of them so that
                 * none linger in the queue indefinitely (seen as input lag).
                 * frames_scheduled indicates the number of frames that are scheduled
                 * to ensure all surfaces' queues are fully drained.
                 */
                frames_scheduled--;
                lock.unlock();

                display_buffer_compositor->composite();

                lock.lock();
            }
        }
    }
    catch(...)
    {
        mir::terminate_with_current_exception();
    }

    void schedule_compositing_unlocked(int num_frames)
    {
        if (num_frames > frames_scheduled)
        {
            frames_scheduled = num_frames;
            run_cv.notify_one();
        }
    }

    void schedule_compositing(int num)
    {
        std::lock_guard<std::mutex> lock{run_mutex};
        schedule_compositing_unlocked(num);
    }

    void stop()
    {
        std::lock_guard<std::mutex> lock{run_mutex};
        running = false;
        run_cv.notify_one();
    }

    void on_cursor_movement_unlocked(geometry::Point const& p)
    {
        if (display_buffer_compositor)
        {
            if (auto cursor = display_buffer_compositor->cursor().lock())
                cursor->move_to(p);
        }
        if (zoom_mag != 1.0f)
            schedule_compositing_unlocked(1);
    }

    void on_cursor_movement(geometry::Point const& p)
    {
        std::lock_guard<std::mutex> lock{run_mutex};
        on_cursor_movement_unlocked(p);
    }

    void zoom_unlocked(float magnification)
    {
        if (auto db = dynamic_cast<Zoomable*>(display_buffer_compositor.get()))
        {
            db->zoom(magnification);
            if (magnification != zoom_mag)
                schedule_compositing_unlocked(1);
        }
        zoom_mag = magnification;
    }

    void zoom(float magnification)
    {
        std::lock_guard<std::mutex> lock{run_mutex};
        zoom_unlocked(magnification);
    }

private:
    std::shared_ptr<mc::DisplayBufferCompositorFactory> const display_buffer_compositor_factory;
    mg::DisplayBuffer& buffer;
    bool running;
    int frames_scheduled;
    std::mutex run_mutex;
    std::condition_variable run_cv;
    std::shared_ptr<CompositorReport> const report;
    std::unique_ptr<DisplayBufferCompositor> display_buffer_compositor;
    float zoom_mag;
};

}
}

mc::MultiThreadedCompositor::MultiThreadedCompositor(
    std::shared_ptr<mg::Display> const& display,
    std::shared_ptr<mc::Scene> const& scene,
    std::shared_ptr<DisplayBufferCompositorFactory> const& db_compositor_factory,
    std::shared_ptr<CompositorReport> const& compositor_report,
    bool compose_on_start)
    : display{display},
      scene{scene},
      display_buffer_compositor_factory{db_compositor_factory},
      report{compositor_report},
      vcursor(std::make_shared<MultiCursor>(*this)),
      state{CompositorState::stopped},
      compose_on_start{compose_on_start}
{
    observer = std::make_shared<ms::LegacySceneChangeNotification>(
    [this]()
    {
        schedule_compositing(1);
    },
    [this](int num)
    {
        schedule_compositing(num);
    });
}

mc::MultiThreadedCompositor::~MultiThreadedCompositor()
{
    stop();
}

void mc::MultiThreadedCompositor::schedule_compositing(int num)
{
    std::unique_lock<std::mutex> lk(state_guard);

    report->scheduled();
    for (auto& f : thread_functors)
        f->schedule_compositing(num);
}

void mc::MultiThreadedCompositor::start()
{
    std::unique_lock<std::mutex> lk(state_guard);
    if (state != CompositorState::stopped)
    {
        return;
    }

    state = CompositorState::starting;
    report->started();

    /* To cleanup state if any code below throws */
    ApplyIfUnwinding cleanup_if_unwinding{
        [this, &lk]{
            destroy_compositing_threads(lk);
        }};

    lk.unlock();
    scene->add_observer(observer);
    lk.lock();

    create_compositing_threads();

    /* Optional first render */
    if (compose_on_start)
    {
        lk.unlock();
        schedule_compositing(1);
    }
}

void mc::MultiThreadedCompositor::stop()
{
    std::unique_lock<std::mutex> lk(state_guard);
    if (state != CompositorState::started)
    {
        return;
    }

    state = CompositorState::stopping;

    /* To cleanup state if any code below throws */
    ApplyIfUnwinding cleanup_if_unwinding{
        [this, &lk]{
            if(!lk.owns_lock()) lk.lock();
            state = CompositorState::started;
        }};

    lk.unlock();
    scene->remove_observer(observer);
    lk.lock();

    destroy_compositing_threads(lk);

    // If the compositor is restarted we've likely got clients blocked
    // so we will need to schedule compositing immediately
    compose_on_start = true;
}

void mc::MultiThreadedCompositor::create_compositing_threads()
{
    /* Start the display buffer compositing threads */
    display->for_each_display_buffer([this](mg::DisplayBuffer& buffer)
    {
        auto thread_functor_raw = new mc::CompositingFunctor{display_buffer_compositor_factory, buffer, report};
        auto thread_functor = std::unique_ptr<mc::CompositingFunctor>(thread_functor_raw);

        threads.push_back(std::thread{std::ref(*thread_functor)});
        thread_functors.push_back(std::move(thread_functor));
    });

    state = CompositorState::started;
}

void mc::MultiThreadedCompositor::destroy_compositing_threads(std::unique_lock<std::mutex>& lock)
{
    /* Could be called during unwinding,
     * ensure the lock is held before changing state
     */
    if(!lock.owns_lock())
        lock.lock();

    for (auto& f : thread_functors)
        f->stop();

    for (auto& t : threads)
        t.join();

    thread_functors.clear();
    threads.clear();

    report->stopped();

    state = CompositorState::stopped;
}

std::weak_ptr<mir::graphics::Cursor> mc::MultiThreadedCompositor::cursor() const
{
    return vcursor;
}

void mc::MultiThreadedCompositor::on_cursor_movement(geometry::Point const& p)
{
    std::unique_lock<std::mutex> lk(state_guard);
    for (auto& f : thread_functors)
        f->on_cursor_movement(p);
}

void mc::MultiThreadedCompositor::zoom(float magnification)
{
    std::unique_lock<std::mutex> lk(state_guard);
    for (auto& f : thread_functors)
        f->zoom(magnification);
}
