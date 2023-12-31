/* l-bus-manager.c
 *
 * Copyright 25.09.2023 NordLex
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "l-bus-manager.h"

#define logid_name          "pizza.pixl.LogiOps"
#define logid_path          "/pizza/pixl/logiops"
#define logid_devices       "pizza.pixl.LogiOps.Devices"
#define logid_device        "pizza.pixl.LogiOps.Device"
#define logid_smart_shift   "pizza.pixl.LogiOps.SmartShift"
#define logid_button        "pizza.pixl.LogiOps.Button"

struct _LBusManager {
            GObject parent_instance;

         GDBusProxy *logid_proxy;
    GDBusConnection *bus_connection;
             GSList *device_paths;
             GSList *button_paths;
};

G_DEFINE_FINAL_TYPE(LBusManager, l_bus_manager, G_TYPE_OBJECT)

GDBusProxy *
get_property_proxy(LBusManager *self, GString *device) {
    GDBusProxy *property_proxy;
    GError *error = NULL;

    property_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                           G_DBUS_PROXY_FLAGS_NONE,
                                           NULL,
                                           logid_name,
                                           device->str,
                                           "org.freedesktop.DBus.Properties",
                                           NULL,
                                           &error);
    g_assert_no_error(error);

    return property_proxy;
}

GDBusProxy *
get_dpi_proxy(LBusManager *self, GString *device) {
    GDBusProxy *dpi_proxy;
    GError *error = NULL;

    dpi_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                      G_DBUS_PROXY_FLAGS_NONE,
                                      NULL,
                                      logid_name,
                                      device->str,
                                      "pizza.pixl.LogiOps.DPI",
                                      NULL,
                                      &error);
    g_assert_no_error(error);

    return dpi_proxy;
}

GDBusProxy *
get_smartshift_proxy(LBusManager *self, GString *device) {
    GDBusProxy *smartshift_proxy;
    GError *error = NULL;

    smartshift_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                              G_DBUS_PROXY_FLAGS_NONE,
                                              NULL,
                                              logid_name,
                                              device->str,
                                              "pizza.pixl.LogiOps.SmartShift",
                                              NULL,
                                              &error);
    g_assert_no_error(error);

    return smartshift_proxy;
}

GDBusProxy *
get_hiresscroll_proxy(LBusManager *self, GString  *device) {
    GDBusProxy *hiresscroll_proxy;
    GError *error = NULL;

    hiresscroll_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                               G_DBUS_PROXY_FLAGS_NONE,
                                               NULL,
                                               logid_name,
                                               device->str,
                                               "pizza.pixl.LogiOps.HiresScroll",
                                               NULL,
                                               &error);
    g_assert_no_error(error);

    return hiresscroll_proxy;
}

GDBusProxy *
get_thumb_wheel_proxy(LBusManager *self, GString *device) {
    GDBusProxy *thumb_wheel_proxy;
    GError *error = NULL;

    thumb_wheel_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                              G_DBUS_PROXY_FLAGS_NONE,
                                              NULL,
                                              logid_name,
                                              device->str,
                                              "pizza.pixl.LogiOps.ThumbWheel",
                                              NULL,
                                              &error);
    g_assert_no_error(error);

    return thumb_wheel_proxy;
}

GDBusProxy *
get_buttons_proxy(LBusManager *self, GString *device) {
    GDBusProxy *buttons_proxy;
    GError *error = NULL;

    buttons_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                         G_DBUS_PROXY_FLAGS_NONE,
                                         NULL,
                                         logid_name,
                                         device->str,
                                         "pizza.pixl.LogiOps.Buttons",
                                         NULL,
                                         &error);
    g_assert_no_error(error);

    return buttons_proxy;
}

GSList *
l_bus_manager_request_devices_list(LBusManager *self) {
    GVariant *result;
    GError *error = NULL;
    GVariantIter *iter;
    gchar *path;

    result = g_dbus_proxy_call_sync(self->logid_proxy,
                                    "Enumerate",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(ao)", &iter);

    while (g_variant_iter_loop(iter, "o", &path))
        self->device_paths = g_slist_append(self->device_paths, g_string_new(path));

    g_variant_iter_free(iter);
    g_variant_unref(result);

    return self->device_paths;
}

GString *
l_bus_manager_request_device_name(LBusManager *self, GString *device) {
    GDBusProxy *property_proxy;
    GVariant *result;
    GError *error = NULL;
    gchar *device_name;

    property_proxy = get_property_proxy(self, device);

    result = g_dbus_proxy_call_sync(property_proxy,
                                    "Get",
                                    g_variant_new("(ss)", logid_device, "Name"),
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);
    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "s", &device_name);
    g_variant_unref(result);

    return g_string_new(device_name);
}

static void
callback_dpi(GObject *object, GAsyncResult *result, gpointer data) {
    GVariant *variant;
    GDBusProxy *proxy = G_DBUS_PROXY(object);
    GError *error = NULL;
    guint16 dpi;

    variant = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL && !g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
        g_warning("Failed to read DPI: %s", error->message);
    } else {
        g_variant_get(variant, "(q)", &dpi);

        g_print("\n|       dpi: %d\n", dpi);
    }
    g_variant_unref(variant);
}

static void
callback_dpis(GObject *object, GAsyncResult *result, gpointer data) {
    GVariant *variant;
    GDBusProxy *proxy = G_DBUS_PROXY(object);
    GError *error = NULL;
    GVariantIter *dpi_iter;
    guint16 dpi_step, dpis;
    gboolean range;

    variant = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL && !g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
        g_warning("Failed to read DPI`s: %s", error->message);
    } else {
        g_variant_get(variant, "(aqqb)", &dpi_iter, &dpi_step, &range);

        while (g_variant_iter_loop(dpi_iter, "q", &dpis)) {
            g_print("|      dpis: %d\n", dpis);
        }

        g_print("|  dpi step: %d\n", dpi_step);
        g_print("| dpi range: %s\n", range ? "true" : "false");
    }
    g_variant_unref(variant);
}

/*
 * Not finished
 *
 */
int
l_bus_manager_request_dpi(LBusManager *self,
                          GString *device,
                          guint16 *dpi,
                          guint16 *dpi_step,
                          guint16 *dpi_min,
                          guint16 *dpi_max,
                          gboolean *range) {
    GDBusProxy *dpi_proxy;
    GVariant *sensor_byte;
    GError *error = NULL;

    dpi_proxy = get_dpi_proxy(self, device);

    sensor_byte = g_dbus_proxy_call_sync(dpi_proxy,
                                    "GetSensors",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    sensor_byte = g_variant_new("(y)", 0); /* Заглушка */

    g_dbus_proxy_call(dpi_proxy,
                      "GetDPI",
                      sensor_byte,
                      G_DBUS_CALL_FLAGS_NONE,
                      -1,
                      NULL,
                      (GAsyncReadyCallback) callback_dpi,
                      &dpi);

    g_dbus_proxy_call(dpi_proxy,
                      "GetDPIs",
                      sensor_byte,
                      G_DBUS_CALL_FLAGS_NONE,
                      -1,
                      NULL,
                      (GAsyncReadyCallback) callback_dpis,
                      NULL);

    return 0;
}

int
l_bus_manager_request_hiresscroll(LBusManager *self, GString *device,
                                   gboolean *hires, gboolean *invert, gboolean *target) {
    GDBusProxy *hires_scroll_proxy;
    GVariant *result;
    GError   *error = NULL;

    hires_scroll_proxy = get_hiresscroll_proxy(self, device);

    result = g_dbus_proxy_call_sync(hires_scroll_proxy,
                                    "GetConfig",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);
    g_variant_get(result, "(bbb)", hires, invert, target);
    g_variant_unref(result);

    return 0;
}

static void
torque_support_request(GDBusProxy *proxy, gboolean *state) {
    GVariant *result;
    GVariant *arguments = g_variant_new("(ss)", logid_smart_shift, "TorqueSupport");
    GError *error = NULL;

    result = g_dbus_proxy_call_sync(proxy,
                                    "Get",
                                    arguments,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "b", state);
    g_variant_unref(result);
}

static void
smartshift_get_config(GDBusProxy *proxy, guchar *active, guchar *threshold, guchar *torque) {
    GVariant *result;
    GError *error = NULL;

    result = g_dbus_proxy_call_sync(proxy,
                                    "GetConfig",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(yyy)", active, threshold, torque);
}

int
l_bus_manager_request_smartshift(LBusManager *self, GString *device, gboolean *torque_support,
                                 guchar *active, guchar *threshold, guchar *torque) {
    GDBusProxy *proxy, *property;

    property = get_property_proxy(self, device);
    proxy = get_smartshift_proxy(self, device);

    torque_support_request(property, torque_support);
    smartshift_get_config(proxy, active, threshold, torque);

    return 0;
}

int
l_bus_manager_request_thumb_wheel(LBusManager *self, GString *device,
                                  gboolean *divert, gboolean *invert) {
    GDBusProxy *thumb_wheel_proxy;
    GVariant *result;
    GError *error = NULL;

    thumb_wheel_proxy = get_thumb_wheel_proxy(self, device);

    result = g_dbus_proxy_call_sync(thumb_wheel_proxy,
                                    "GetConfig",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(bb)", divert, invert);

    return 0;
}

int
l_bus_manager_request_button_info(LBusManager *self, GString *button, guint16 *cid, guint16 *task_id) {
    GDBusProxy *property_proxy;
    GVariant *result;
    GError *error = NULL;

    property_proxy = get_property_proxy(self, button);

    result = g_dbus_proxy_call_sync(property_proxy,
                                    "Get",
                                    g_variant_new("(ss)", logid_button, "ControlID"),
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "q", cid);

    result = g_dbus_proxy_call_sync(property_proxy,
                                    "Get",
                                    g_variant_new("(ss)", logid_button, "TaskID"),
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "q", task_id);

    return 0;
}

GSList *
l_bus_manager_request_buttons_list(LBusManager *self, GString *device) {
    GDBusProxy *device_proxy;
    GVariant *result;
    GError *error = NULL;
    GVariantIter *iter;
    gchar *path;

    device_proxy = get_buttons_proxy(self, device);

    result = g_dbus_proxy_call_sync(device_proxy,
                                    "Enumerate",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(ao)", &iter);
    self->button_paths = NULL;

    while (g_variant_iter_loop(iter, "o", &path))
        self->button_paths = g_slist_append(self->button_paths, g_string_new(path));

    g_variant_iter_free(iter);
    g_variant_unref(result);

    return self->button_paths;
}

static void
test_bus_manager(LBusManager *self) {

}

LBusManager *
l_bus_manager_new(void) {
    return g_object_new(L_TYPE_BUS_MANAGER, NULL);
}

static void
l_bus_manager_class_init(LBusManagerClass *klass) {}

static void
l_bus_manager_init(LBusManager *self) {
    GError *error = NULL;

    self->bus_connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    g_assert_no_error(error);

    self->logid_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                              G_DBUS_PROXY_FLAGS_NONE,
                                              NULL,
                                              logid_name,
                                              logid_path,
                                              logid_devices,
                                              NULL,
                                              &error);
    g_assert_no_error(error);
}