/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois<kevin.dubois@canonical.com>
 */

#include "mir_client/android/mir_native_window.h"
#include "mir_client/android/android_client_platform.h"
#include "mir_client/android/android_registrar_gralloc.h"
#include "mir_client/android/android_client_buffer_depository.h"
#include "mir_client/mir_connection.h"
#include "mir_client/native_client_platform_factory.h"

#include <EGL/egl.h>

namespace mcl=mir::client;
namespace mcla=mir::client::android;

namespace
{

struct EmptyDeleter
{
    void operator()(void* )
    {
    }
};

class AndroidEGLNativeDisplayContainer : public mcl::EGLNativeDisplayContainer
{
public:
    EGLNativeDisplayType get_egl_native_display()
    {
        return EGL_DEFAULT_DISPLAY;
    }
};

}

std::shared_ptr<mcl::ClientPlatform>
mcl::NativeClientPlatformFactory::create_client_platform(mcl::ClientContext* /*context*/)
{
    return std::make_shared<mcla::AndroidClientPlatform>();
}

std::shared_ptr<mcl::ClientBufferDepository> mcla::AndroidClientPlatform::create_platform_depository()
{
    const hw_module_t *hw_module;
    int error = hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &hw_module);
    if (error < 0)
    {
        throw std::runtime_error("Could not open hardware module");
    }

    gralloc_module_t* gr_dev = (gralloc_module_t*) hw_module;
    /* we use an empty deleter because hw_get_module does not give us the ownership of the ptr */
    EmptyDeleter empty_del;
    auto gralloc_dev = std::shared_ptr<gralloc_module_t>(gr_dev, empty_del);
    auto registrar = std::make_shared<mcla::AndroidRegistrarGralloc>(gralloc_dev); 
    return std::make_shared<mcla::AndroidClientBufferDepository>(registrar);
}

namespace
{
struct MirNativeWindowDeleter
{
    MirNativeWindowDeleter(mcla::MirNativeWindow* window)
     : window(window) {}

    void operator()(EGLNativeWindowType* type )
    {
        delete type;
        delete window;
    }

private:
    mcla::MirNativeWindow *window;
};
}

std::shared_ptr<EGLNativeWindowType> mcla::AndroidClientPlatform::create_egl_window(ClientSurface *surface)
{
    auto mir_native_window = new mcla::MirNativeWindow(surface);
    auto egl_native_window = new EGLNativeWindowType;
    *egl_native_window = mir_native_window;
    MirNativeWindowDeleter deleter = MirNativeWindowDeleter(mir_native_window); 
    return std::shared_ptr<EGLNativeWindowType>(egl_native_window, deleter);
}

std::shared_ptr<mcl::EGLNativeDisplayContainer>
mcla::AndroidClientPlatform::create_egl_native_display()
{
    return std::make_shared<AndroidEGLNativeDisplayContainer>();
}
