/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from xdg-shell.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include "xdg-shell_wrapper.h"

#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <wayland-server-core.h>

#include "mir/log.h"

namespace mir
{
namespace wayland
{
extern struct wl_interface const wl_output_interface_data;
extern struct wl_interface const wl_seat_interface_data;
extern struct wl_interface const wl_surface_interface_data;
extern struct wl_interface const xdg_popup_interface_data;
extern struct wl_interface const xdg_positioner_interface_data;
extern struct wl_interface const xdg_surface_interface_data;
extern struct wl_interface const xdg_toplevel_interface_data;
extern struct wl_interface const xdg_wm_base_interface_data;
}
}

namespace mw = mir::wayland;

namespace
{
struct wl_interface const* all_null_types [] {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr};
}

// XdgWmBase

struct mw::XdgWmBase::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgWmBase::destroy()");
        }
    }

    static void create_positioner_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &xdg_positioner_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
            me->create_positioner(id_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgWmBase::create_positioner()");
        }
    }

    static void get_xdg_surface_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* surface)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &xdg_surface_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
            me->get_xdg_surface(id_resolved, surface);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgWmBase::get_xdg_surface()");
        }
    }

    static void pong_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
            me->pong(serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgWmBase::pong()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
    }

    static void bind_thunk(struct wl_client* client, void* data, uint32_t version, uint32_t id)
    {
        auto me = static_cast<XdgWmBase::Global*>(data);
        auto resource = wl_resource_create(
            client,
            &xdg_wm_base_interface_data,
            std::min((int)version, Thunks::supported_version),
            id);
        if (resource == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            me->bind(resource);
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgWmBase global bind");
        }
    }

    static struct wl_interface const* create_positioner_types[];
    static struct wl_interface const* get_xdg_surface_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgWmBase::Thunks::supported_version = 1;

mw::XdgWmBase::XdgWmBase(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgWmBase::~XdgWmBase()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgWmBase::send_ping_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::ping, serial);
}

bool mw::XdgWmBase::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_wm_base_interface_data, Thunks::request_vtable);
}

mw::XdgWmBase::Global::Global(wl_display* display, Version<1>)
    : wayland::Global{
          wl_global_create(
              display,
              &xdg_wm_base_interface_data,
              Thunks::supported_version,
              this,
              &Thunks::bind_thunk)}
{
}

auto mw::XdgWmBase::Global::interface_name() const -> char const*
{
    return XdgWmBase::interface_name;
}

struct wl_interface const* mw::XdgWmBase::Thunks::create_positioner_types[] {
    &xdg_positioner_interface_data};

struct wl_interface const* mw::XdgWmBase::Thunks::get_xdg_surface_types[] {
    &xdg_surface_interface_data,
    &wl_surface_interface_data};

struct wl_message const mw::XdgWmBase::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"create_positioner", "n", create_positioner_types},
    {"get_xdg_surface", "no", get_xdg_surface_types},
    {"pong", "u", all_null_types}};

struct wl_message const mw::XdgWmBase::Thunks::event_messages[] {
    {"ping", "u", all_null_types}};

void const* mw::XdgWmBase::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::create_positioner_thunk,
    (void*)Thunks::get_xdg_surface_thunk,
    (void*)Thunks::pong_thunk};

mw::XdgWmBase* mw::XdgWmBase::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &xdg_wm_base_interface_data, XdgWmBase::Thunks::request_vtable))
    {
        return static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgPositioner

struct mw::XdgPositioner::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::destroy()");
        }
    }

    static void set_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_size()");
        }
    }

    static void set_anchor_rect_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_anchor_rect(x, y, width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_anchor_rect()");
        }
    }

    static void set_anchor_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t anchor)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_anchor(anchor);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_anchor()");
        }
    }

    static void set_gravity_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t gravity)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_gravity(gravity);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_gravity()");
        }
    }

    static void set_constraint_adjustment_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t constraint_adjustment)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_constraint_adjustment(constraint_adjustment);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_constraint_adjustment()");
        }
    }

    static void set_offset_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y)
    {
        try
        {
            auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
            me->set_offset(x, y);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPositioner::set_offset()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
    }

    static struct wl_message const request_messages[];
    static void const* request_vtable[];
};

int const mw::XdgPositioner::Thunks::supported_version = 1;

mw::XdgPositioner::XdgPositioner(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgPositioner::~XdgPositioner()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

bool mw::XdgPositioner::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_positioner_interface_data, Thunks::request_vtable);
}

struct wl_message const mw::XdgPositioner::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_size", "ii", all_null_types},
    {"set_anchor_rect", "iiii", all_null_types},
    {"set_anchor", "u", all_null_types},
    {"set_gravity", "u", all_null_types},
    {"set_constraint_adjustment", "u", all_null_types},
    {"set_offset", "ii", all_null_types}};

void const* mw::XdgPositioner::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_size_thunk,
    (void*)Thunks::set_anchor_rect_thunk,
    (void*)Thunks::set_anchor_thunk,
    (void*)Thunks::set_gravity_thunk,
    (void*)Thunks::set_constraint_adjustment_thunk,
    (void*)Thunks::set_offset_thunk};

mw::XdgPositioner* mw::XdgPositioner::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &xdg_positioner_interface_data, XdgPositioner::Thunks::request_vtable))
    {
        return static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgSurface

struct mw::XdgSurface::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurface::destroy()");
        }
    }

    static void get_toplevel_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &xdg_toplevel_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        try
        {
            auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
            me->get_toplevel(id_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurface::get_toplevel()");
        }
    }

    static void get_popup_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* parent, struct wl_resource* positioner)
    {
        wl_resource* id_resolved{
            wl_resource_create(client, &xdg_popup_interface_data, wl_resource_get_version(resource), id)};
        if (id_resolved == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
            me->get_popup(id_resolved, parent_resolved, positioner);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurface::get_popup()");
        }
    }

    static void set_window_geometry_thunk(struct wl_client* client, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
            me->set_window_geometry(x, y, width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurface::set_window_geometry()");
        }
    }

    static void ack_configure_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
            me->ack_configure(serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgSurface::ack_configure()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* get_toplevel_types[];
    static struct wl_interface const* get_popup_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgSurface::Thunks::supported_version = 1;

mw::XdgSurface::XdgSurface(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgSurface::~XdgSurface()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgSurface::send_configure_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::configure, serial);
}

bool mw::XdgSurface::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_surface_interface_data, Thunks::request_vtable);
}

struct wl_interface const* mw::XdgSurface::Thunks::get_toplevel_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mw::XdgSurface::Thunks::get_popup_types[] {
    &xdg_popup_interface_data,
    &xdg_surface_interface_data,
    &xdg_positioner_interface_data};

struct wl_message const mw::XdgSurface::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"get_toplevel", "n", get_toplevel_types},
    {"get_popup", "n?oo", get_popup_types},
    {"set_window_geometry", "iiii", all_null_types},
    {"ack_configure", "u", all_null_types}};

struct wl_message const mw::XdgSurface::Thunks::event_messages[] {
    {"configure", "u", all_null_types}};

void const* mw::XdgSurface::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::get_toplevel_thunk,
    (void*)Thunks::get_popup_thunk,
    (void*)Thunks::set_window_geometry_thunk,
    (void*)Thunks::ack_configure_thunk};

mw::XdgSurface* mw::XdgSurface::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &xdg_surface_interface_data, XdgSurface::Thunks::request_vtable))
    {
        return static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgToplevel

struct mw::XdgToplevel::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::destroy()");
        }
    }

    static void set_parent_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* parent)
    {
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_parent(parent_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_parent()");
        }
    }

    static void set_title_thunk(struct wl_client* client, struct wl_resource* resource, char const* title)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_title(title);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_title()");
        }
    }

    static void set_app_id_thunk(struct wl_client* client, struct wl_resource* resource, char const* app_id)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_app_id(app_id);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_app_id()");
        }
    }

    static void show_window_menu_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, int32_t x, int32_t y)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->show_window_menu(seat, serial, x, y);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::show_window_menu()");
        }
    }

    static void move_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->move(seat, serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::move()");
        }
    }

    static void resize_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, uint32_t edges)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->resize(seat, serial, edges);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::resize()");
        }
    }

    static void set_max_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_max_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_max_size()");
        }
    }

    static void set_min_size_thunk(struct wl_client* client, struct wl_resource* resource, int32_t width, int32_t height)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_min_size(width, height);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_min_size()");
        }
    }

    static void set_maximized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_maximized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_maximized()");
        }
    }

    static void unset_maximized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->unset_maximized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::unset_maximized()");
        }
    }

    static void set_fullscreen_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* output)
    {
        std::experimental::optional<struct wl_resource*> output_resolved;
        if (output != nullptr)
        {
            output_resolved = {output};
        }
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_fullscreen(output_resolved);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_fullscreen()");
        }
    }

    static void unset_fullscreen_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->unset_fullscreen();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::unset_fullscreen()");
        }
    }

    static void set_minimized_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
            me->set_minimized();
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgToplevel::set_minimized()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* set_parent_types[];
    static struct wl_interface const* show_window_menu_types[];
    static struct wl_interface const* move_types[];
    static struct wl_interface const* resize_types[];
    static struct wl_interface const* set_fullscreen_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgToplevel::Thunks::supported_version = 1;

mw::XdgToplevel::XdgToplevel(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgToplevel::~XdgToplevel()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgToplevel::send_configure_event(int32_t width, int32_t height, struct wl_array* states) const
{
    wl_resource_post_event(resource, Opcode::configure, width, height, states);
}

void mw::XdgToplevel::send_close_event() const
{
    wl_resource_post_event(resource, Opcode::close);
}

bool mw::XdgToplevel::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_toplevel_interface_data, Thunks::request_vtable);
}

struct wl_interface const* mw::XdgToplevel::Thunks::set_parent_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mw::XdgToplevel::Thunks::show_window_menu_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::move_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::resize_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr};

struct wl_interface const* mw::XdgToplevel::Thunks::set_fullscreen_types[] {
    &wl_output_interface_data};

struct wl_message const mw::XdgToplevel::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_parent", "?o", set_parent_types},
    {"set_title", "s", all_null_types},
    {"set_app_id", "s", all_null_types},
    {"show_window_menu", "ouii", show_window_menu_types},
    {"move", "ou", move_types},
    {"resize", "ouu", resize_types},
    {"set_max_size", "ii", all_null_types},
    {"set_min_size", "ii", all_null_types},
    {"set_maximized", "", all_null_types},
    {"unset_maximized", "", all_null_types},
    {"set_fullscreen", "?o", set_fullscreen_types},
    {"unset_fullscreen", "", all_null_types},
    {"set_minimized", "", all_null_types}};

struct wl_message const mw::XdgToplevel::Thunks::event_messages[] {
    {"configure", "iia", all_null_types},
    {"close", "", all_null_types}};

void const* mw::XdgToplevel::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_parent_thunk,
    (void*)Thunks::set_title_thunk,
    (void*)Thunks::set_app_id_thunk,
    (void*)Thunks::show_window_menu_thunk,
    (void*)Thunks::move_thunk,
    (void*)Thunks::resize_thunk,
    (void*)Thunks::set_max_size_thunk,
    (void*)Thunks::set_min_size_thunk,
    (void*)Thunks::set_maximized_thunk,
    (void*)Thunks::unset_maximized_thunk,
    (void*)Thunks::set_fullscreen_thunk,
    (void*)Thunks::unset_fullscreen_thunk,
    (void*)Thunks::set_minimized_thunk};

mw::XdgToplevel* mw::XdgToplevel::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &xdg_toplevel_interface_data, XdgToplevel::Thunks::request_vtable))
    {
        return static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

// XdgPopup

struct mw::XdgPopup::Thunks
{
    static int const supported_version;

    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        try
        {
            wl_resource_destroy(resource);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPopup::destroy()");
        }
    }

    static void grab_thunk(struct wl_client* client, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        try
        {
            auto me = static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
            me->grab(seat, serial);
        }
        catch(ProtocolError const& err)
        {
            wl_resource_post_error(err.resource(), err.code(), "%s", err.message());
        }
        catch(...)
        {
            internal_error_processing_request(client, "XdgPopup::grab()");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* grab_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

int const mw::XdgPopup::Thunks::supported_version = 1;

mw::XdgPopup::XdgPopup(struct wl_resource* resource, Version<1>)
    : client{wl_resource_get_client(resource)},
      resource{resource}
{
    if (resource == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

mw::XdgPopup::~XdgPopup()
{
    wl_resource_set_implementation(resource, nullptr, nullptr, nullptr);
}

void mw::XdgPopup::send_configure_event(int32_t x, int32_t y, int32_t width, int32_t height) const
{
    wl_resource_post_event(resource, Opcode::configure, x, y, width, height);
}

void mw::XdgPopup::send_popup_done_event() const
{
    wl_resource_post_event(resource, Opcode::popup_done);
}

bool mw::XdgPopup::is_instance(wl_resource* resource)
{
    return wl_resource_instance_of(resource, &xdg_popup_interface_data, Thunks::request_vtable);
}

struct wl_interface const* mw::XdgPopup::Thunks::grab_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_message const mw::XdgPopup::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"grab", "ou", grab_types}};

struct wl_message const mw::XdgPopup::Thunks::event_messages[] {
    {"configure", "iiii", all_null_types},
    {"popup_done", "", all_null_types}};

void const* mw::XdgPopup::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::grab_thunk};

mw::XdgPopup* mw::XdgPopup::from(struct wl_resource* resource)
{
    if (wl_resource_instance_of(resource, &xdg_popup_interface_data, XdgPopup::Thunks::request_vtable))
    {
        return static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
    }
    return nullptr;
}

namespace mir
{
namespace wayland
{

struct wl_interface const xdg_wm_base_interface_data {
    mw::XdgWmBase::interface_name,
    mw::XdgWmBase::Thunks::supported_version,
    4, mw::XdgWmBase::Thunks::request_messages,
    1, mw::XdgWmBase::Thunks::event_messages};

struct wl_interface const xdg_positioner_interface_data {
    mw::XdgPositioner::interface_name,
    mw::XdgPositioner::Thunks::supported_version,
    7, mw::XdgPositioner::Thunks::request_messages,
    0, nullptr};

struct wl_interface const xdg_surface_interface_data {
    mw::XdgSurface::interface_name,
    mw::XdgSurface::Thunks::supported_version,
    5, mw::XdgSurface::Thunks::request_messages,
    1, mw::XdgSurface::Thunks::event_messages};

struct wl_interface const xdg_toplevel_interface_data {
    mw::XdgToplevel::interface_name,
    mw::XdgToplevel::Thunks::supported_version,
    14, mw::XdgToplevel::Thunks::request_messages,
    2, mw::XdgToplevel::Thunks::event_messages};

struct wl_interface const xdg_popup_interface_data {
    mw::XdgPopup::interface_name,
    mw::XdgPopup::Thunks::supported_version,
    2, mw::XdgPopup::Thunks::request_messages,
    2, mw::XdgPopup::Thunks::event_messages};

}
}
