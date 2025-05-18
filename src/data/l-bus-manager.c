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

#define logid_name                  "pizza.pixl.LogiOps"
#define logid_path                  "/pizza/pixl/logiops"
#define logid_devices               "pizza.pixl.LogiOps.Devices"
#define logid_device                "pizza.pixl.LogiOps.Device"
#define logid_smart_shift           "pizza.pixl.LogiOps.SmartShift"
#define logid_button                "pizza.pixl.LogiOps.Button"
#define iface_action_keypress       "pizza.pixl.LogiOps.Action.Keypress"
#define iface_action_gesture        "pizza.pixl.LogiOps.Action.Gesture"
#define iface_action_cycle_dpi      "pizza.pixl.LogiOps.Action.CycleDPI"
#define iface_action_change_dpi     "pizza.pixl.LogiOps.Action.ChangeDPI"
#define iface_action_change_host    "pizza.pixl.LogiOps.Action.ChangeHost"

struct _LBusManager {
    GObject parent_instance;

    GDBusProxy *logid_proxy;
    GDBusConnection *bus_connection;
    GSList *device_paths;
    GSList *button_paths;
    LKeyCode *key_code_converter;
};

G_DEFINE_FINAL_TYPE(LBusManager, l_bus_manager, G_TYPE_OBJECT)


static void
get_logid_proxy(LBusManager *self) {
    GError *error = NULL;

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

static GDBusProxy *
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

static GDBusProxy *
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

static GDBusProxy *
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

static GDBusProxy *
get_hiresscroll_proxy(LBusManager *self, GString *device) {
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

static GDBusProxy *
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

static GDBusProxy *
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

static GDBusProxy *
get_button_proxy(LBusManager *self, GString *button) {
    GDBusProxy *button_proxy;
    GError *error = NULL;

    button_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          logid_name,
                                          button->str,
                                          "pizza.pixl.LogiOps.Button",
                                          NULL,
                                          &error);
    g_assert_no_error(error);

    return button_proxy;
}

static GDBusProxy *
get_action_proxy(LBusManager *self, GString *button, const char *iface_name) {
    GDBusProxy *action_proxy;
    GError *error = NULL;

    action_proxy = g_dbus_proxy_new_sync(self->bus_connection,
                                         G_DBUS_PROXY_FLAGS_NONE,
                                         NULL,
                                         logid_name,
                                         button->str,
                                         iface_name,
                                         NULL,
                                         &error);
    g_assert_no_error(error);

    return action_proxy;
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
    Dpi *dpi = (Dpi *) data;

    variant = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL && !g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
        g_warning("Failed to read DPI: %s", error->message);
    } else {
        guint16 value;
        g_variant_get(variant, "(q)", &value);
        dpi->dpi = (gint) value;
    }
    g_variant_unref(variant);
}

static void
callback_dpis(GObject *object, GAsyncResult *result, gpointer data) {
    GDBusProxy *proxy = G_DBUS_PROXY(object);
    Dpi *dpi = (Dpi *) data;
    GVariant *variant;
    GError *error = NULL;
    GVariantIter *dpi_iter;
    guint16 dpi_step, dpis;
    gboolean range;

    variant = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL && !g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
        g_warning("Failed to read DPI`s: %s", error->message);
    } else {
        guint16 dpi_buf = 0;
        g_variant_get(variant, "(aqqb)", &dpi_iter, &dpi_step, &range);

        while (g_variant_iter_loop(dpi_iter, "q", &dpis)) {
            if (dpi_buf == 0) {
                dpi_buf = dpis;
            } else {
                if (dpi_buf < dpis) {
                    dpi->min = dpi_buf;
                    dpi->max = dpis;
                } else {
                    dpi->min = dpis;
                    dpi->max = dpi_buf;
                }
            }
        }

        dpi->step = (gint) dpi_step;
        dpi->range = range;
    }

    g_variant_unref(variant);
}

int
l_bus_manager_request_dpi(LBusManager *self, GString *device, Dpi *dpi) {
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

    sensor_byte = g_variant_new("(y)", 0); /** Заглушка **/

    g_dbus_proxy_call(dpi_proxy,
                      "GetDPI",
                      sensor_byte,
                      G_DBUS_CALL_FLAGS_NONE,
                      -1,
                      NULL,
                      (GAsyncReadyCallback) callback_dpi,
                      dpi);

    g_dbus_proxy_call(dpi_proxy,
                      "GetDPIs",
                      sensor_byte,
                      G_DBUS_CALL_FLAGS_NONE,
                      -1,
                      NULL,
                      (GAsyncReadyCallback) callback_dpis,
                      dpi);

    return 0;
}

int
l_bus_manager_request_hiresscroll(LBusManager *self, GString *device, Hiresscroll *hiresscroll) {
    GDBusProxy *hires_scroll_proxy;
    GVariant *result;
    GError *error = NULL;
    gboolean hires, invert, target;

    hires_scroll_proxy = get_hiresscroll_proxy(self, device);

    result = g_dbus_proxy_call_sync(hires_scroll_proxy,
                                    "GetConfig",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);
    g_variant_get(result, "(bbb)", &hires, &invert, &target);
    g_variant_unref(result);

    hiresscroll->hires = hires;
    hiresscroll->invert = invert;
    hiresscroll->target = target;

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
l_bus_manager_request_smartshift(LBusManager *self, GString *device, Smartshift *smartshift) {
    GDBusProxy *proxy, *property;
    gboolean torque_support;
    guchar active, threshold, torque;

    property = get_property_proxy(self, device);
    proxy = get_smartshift_proxy(self, device);

    torque_support_request(property, &torque_support);
    smartshift_get_config(proxy, &active, &threshold, &torque);

    smartshift->torque_support = torque_support;
    smartshift->on = active;
    smartshift->threshold = threshold;
    smartshift->torque = torque;

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
l_bus_manager_request_button_info(LBusManager *self, GString *button,
                                  guint16 *cid, guint16 *task_id,
                                  gboolean *gesture_support, gboolean *remappable) {
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

    result = g_dbus_proxy_call_sync(property_proxy,
                                    "Get",
                                    g_variant_new("(ss)", logid_button, "GestureSupport"),
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "b", gesture_support);

    result = g_dbus_proxy_call_sync(property_proxy,
                                    "Get",
                                    g_variant_new("(ss)", logid_button, "Remappable"),
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);
    g_assert_no_error(error);

    g_variant_get(result, "(v)", &result);
    g_variant_get(result, "b", remappable);

    return 0;
}

static int
request_keypress_action(LBusManager *self, GString *button, Keypress *keypress) {
    GVariant *result;
    GError *error = NULL;
    GVariantIter *iter;
    GSList *keys = NULL;
    gchar *key;
    GDBusProxy *action_proxy = get_action_proxy(self, button, iface_action_keypress);

    result = g_dbus_proxy_call_sync(action_proxy,
                                    "GetKeys",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);

    if (g_error_matches(error, 146, 19)) return 1;
    g_assert_no_error(error);

    g_variant_get(result, "(as)", &iter);

    while (g_variant_iter_loop(iter, "s", &key)) {
        guint *key_code = l_key_code_kernel_to_gdk(self->key_code_converter, key);
        keys = g_slist_append(keys, GUINT_TO_POINTER(*key_code));
    }

    keypress->keys = keys;
    g_variant_iter_free(iter);
    g_variant_unref(result);

    return 0;
}

int
l_bus_manager_set_keypress_action(LBusManager *self, GString *button, Keypress *keypress) {
    GError *error = NULL;
    GDBusProxy *action_proxy = get_action_proxy(self, button, iface_action_keypress);
    GSList *temp = keypress->keys;
    GVariantBuilder *builder = g_variant_builder_new(G_VARIANT_TYPE("as"));
    GVariant *parameters;

    while (temp != NULL) {
        char **key = l_key_code_gdk_to_kernel(self->key_code_converter,
                                              GPOINTER_TO_UINT(temp->data));
        g_variant_builder_add(builder, "s", *key);
        temp = g_slist_next(temp);
    }

    parameters = g_variant_new("(as)", builder);
    g_variant_builder_unref(builder);

    g_dbus_proxy_call_sync(action_proxy,
                           "SetKeys",
                           parameters,
                           G_DBUS_CALL_FLAGS_NONE,
                           -1,
                           NULL,
                           &error);

    g_assert_no_error(error);

    return 0;
}

static int
request_cycle_dpi_action(LBusManager *self, GString *button, CycleDPI *cycle_dpi) {
    GVariant *result;
    GError *error = NULL;
    GVariantIter *iter;
    GSList *dpis = NULL;
    guint dpi;
    GDBusProxy *action_proxy = get_action_proxy(self, button, iface_action_cycle_dpi);

    result = g_dbus_proxy_call_sync(action_proxy,
                                    "GetDPIs",
                                    NULL,
                                    G_DBUS_CALL_FLAGS_NONE,
                                    -1,
                                    NULL,
                                    &error);

    if (g_error_matches(error, 146, 19)) return 1;

    g_assert_no_error(error);

    g_variant_get(result, "(ai)", &iter);

    while (g_variant_iter_loop(iter, "i", &dpi))
        dpis = g_slist_append(dpis, GUINT_TO_POINTER(dpi));

    cycle_dpi->dpis = dpis;
    g_variant_iter_free(iter);
    g_variant_unref(result);

    return 0;
}

int
l_bus_manager_set_cycle_dpi_action(LBusManager *self, GString *button, CycleDPI *cycle_dpi) {
    GError *error = NULL;
    GDBusProxy *action_proxy = get_action_proxy(self, button, iface_action_cycle_dpi);
    GSList *dpis = cycle_dpi->dpis;
    GVariantBuilder *builder = g_variant_builder_new(G_VARIANT_TYPE("ai"));
    GVariant *parameters;

    while (dpis != NULL) {
        g_variant_builder_add(builder, "i", GPOINTER_TO_UINT(dpis->data));
        dpis = g_slist_next(dpis);
    }

    parameters = g_variant_new("(ai)", builder);
    g_variant_builder_unref(builder);

    g_dbus_proxy_call_sync(action_proxy,
                           "SetDPIs",
                           parameters,
                           G_DBUS_CALL_FLAGS_NONE,
                           -1,
                           NULL,
                           &error);

    g_assert_no_error(error);

    return 0;
}

int
l_bus_manager_request_button_action(LBusManager *self, GString *button, Action *action) {
    Keypress *keypress = g_malloc(sizeof(Keypress));
    CycleDPI *cycle_dpi = g_malloc(sizeof(CycleDPI));

    if (!request_keypress_action(self, button, keypress)) {
        action->type = KEYPRESS;
        action->self = keypress;
    } else if (!request_cycle_dpi_action(self, button, cycle_dpi)) {
        action->type = CYCLE_DPI;
        action->self = cycle_dpi;
    } else {
        action->type = DEFAULT;
        action->self = NULL;
    }

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

LBusManager *
l_bus_manager_new(void) {
    return g_object_new(L_TYPE_BUS_MANAGER, NULL);
}

static void
l_bus_manager_class_init(LBusManagerClass *klass) {}

static void
l_bus_manager_init(LBusManager *self) {
    GError *error = NULL;
    self->key_code_converter = l_key_code_new();
    self->bus_connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    g_assert_no_error(error);
}