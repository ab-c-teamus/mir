/*
 * Copyright © 2021 Canonical Ltd.
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
 * Authored by: William Wold <william.wold@canonical.com>
 */

#ifndef MIR_FRONTEND_INPUT_METHOD_GRAB_KEYBOARD_V2_H
#define MIR_FRONTEND_INPUT_METHOD_GRAB_KEYBOARD_V2_H

#include "input-method-unstable-v2_wrapper.h"
#include "keyboard_helper.h"

namespace mir
{
class Executor;
namespace input
{
class CompositeEventFilter;
}
namespace frontend
{
class WlSeat;

/// A keyboard that sends all key events to it's client without ever entering a surface
class InputMethodGrabKeyboardV2
    : public wayland::InputMethodKeyboardGrabV2,
      public KeyboardImpl
{
public:
    InputMethodGrabKeyboardV2(
        wl_resource* resource,
        WlSeat& seat,
        std::shared_ptr<Executor> const& wayland_executor,
        std::shared_ptr<input::CompositeEventFilter> const& event_filter);

private:
    class Handler;

    std::shared_ptr<Handler> const handler;
    std::unique_ptr<KeyboardHelper> const helper;

    /// KeyboardImpl overrides
    /// @{
    void send_repeat_info(int32_t rate, int32_t delay) override;
    void send_keymap_xkb_v1(mir::Fd const& fd, size_t length) override;
    void send_key(uint32_t timestamp, int scancode, bool down) override;
    void send_modifiers(uint32_t depressed, uint32_t latched, uint32_t locked, uint32_t group) override;
    /// @}
};
}
}

#endif // MIR_FRONTEND_INPUT_METHOD_GRAB_KEYBOARD_V2_H
