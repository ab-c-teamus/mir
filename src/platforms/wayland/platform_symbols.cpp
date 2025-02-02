/*
 * Copyright © 2019 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#include <mir/graphics/platform.h>

#include "wayland_display.h"
#include "platform.h"

#include <mir/assert_module_entry_point.h>
#include <mir/libname.h>
#include <mir/options/program_option.h>

namespace mg = mir::graphics;
namespace mo = mir::options;
namespace mgw = mir::graphics::wayland;
namespace mpw = mir::platform::wayland;

namespace
{
mir::ModuleProperties const description = {
    "mir:wayland",
    MIR_VERSION_MAJOR,
    MIR_VERSION_MINOR,
    MIR_VERSION_MICRO,
    mir::libname()
};
}

mir::UniqueModulePtr<mg::DisplayPlatform> create_display_platform(
    std::shared_ptr<mo::Option> const& options,
    std::shared_ptr<mir::EmergencyCleanupRegistry> const&,
    std::shared_ptr<mir::ConsoleServices> const& /*console*/,
    std::shared_ptr<mg::DisplayReport> const& report)
{
    mir::assert_entry_point_signature<mg::CreateDisplayPlatform>(&create_display_platform);
    return mir::make_module_ptr<mgw::Platform>(mpw::connection(*options), report);
}

auto create_rendering_platform(
    mo::Option const&,
    mir::EmergencyCleanupRegistry&) -> mir::UniqueModulePtr<mg::RenderingPlatform>
{
    mir::assert_entry_point_signature<mg::CreateRenderPlatform>(&create_rendering_platform);
    return mir::make_module_ptr<mgw::RenderingPlatform>();
}

void add_graphics_platform_options(boost::program_options::options_description& config)
{
    mir::assert_entry_point_signature<mg::AddPlatformOptions>(&add_graphics_platform_options);
    mpw::add_connection_options(config);
}

mg::PlatformPriority probe_graphics_platform(
    mo::ProgramOption const& options)
{

    return mpw::connection_options_supplied(options) ? mg::PlatformPriority::best :
           mg::PlatformPriority::unsupported;
}

auto probe_rendering_platform(
    std::shared_ptr<mir::ConsoleServices> const&,
    mo::ProgramOption const& options) -> mg::PlatformPriority
{
    mir::assert_entry_point_signature<mg::PlatformProbe>(&probe_rendering_platform);
    return probe_graphics_platform(options);
}

auto probe_display_platform(
    std::shared_ptr<mir::ConsoleServices> const&,
    mo::ProgramOption const& options) -> mg::PlatformPriority
{
    mir::assert_entry_point_signature<mg::PlatformProbe>(&probe_display_platform);
    return probe_graphics_platform(options);
}

mir::ModuleProperties const* describe_graphics_module()
{
    mir::assert_entry_point_signature<mg::DescribeModule>(&describe_graphics_module);
    return &description;
}
