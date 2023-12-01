/* l-data-manager.c
 *
 * Copyright 10.11.2023 NordLex
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

#include "l-data-manager.h"


struct _LDataManager {
    GObject parent_instance;

    LBusManager *bus_manager;
};

G_DEFINE_FINAL_TYPE(LDataManager, l_data_manager, G_TYPE_OBJECT)

GString *
find_device(LBusManager *bus, GSList *list, GString *description_name) {
    GSList *temp;

    if (list == NULL) return NULL;
    temp = list;

    while (temp != NULL) {
        GString *device = temp->data;
        GString *device_name = l_bus_manager_request_device_name(bus, device);

        if (g_string_equal(device_name, description_name))
            return device;
        temp = g_slist_next(temp);
    }

    return NULL;
}

static void
set_default_button_conf(gpointer *conf) {
    conf = NULL;
}

gpointer
find_conf_cid(gint cid, GSList *buttons_conf) {
    GSList *temp = buttons_conf;

    while (temp != NULL) {
        Button *conf = temp->data;
        if (conf->cid == cid) {
            return conf;
        }
        temp = g_slist_next(temp);
    }

    return NULL;
}

static void /*  Заглушка    */
fill_device_conf(LBusManager *bus, GString *device, LDevice *device_conf) {
    GSList *middle_actions = NULL;
    GSList *top_actions = NULL;
    GSList *forward_actions = NULL;
    GSList *back_actions = NULL;
    GSList *hwheel_actions = NULL;
    GSList *gesture_actions = NULL;

    middle_actions = g_slist_append(middle_actions, (char *) "KEY_LEFTMETA");
    middle_actions = g_slist_append(middle_actions, (char *) "KEY_TAB");

    top_actions = g_slist_append(top_actions, (char *) "KEY_LEFTCTRL");
    top_actions = g_slist_append(top_actions, (char *) "KEY_L");

    forward_actions = g_slist_append(forward_actions, (char *) "KEY_LEFTCTRL");
    forward_actions = g_slist_append(forward_actions, (char *) "KEY_C");

    back_actions = g_slist_append(back_actions, (char *) "KEY_LEFTCTRL");
    back_actions = g_slist_append(back_actions, (char *) "KEY_V");

    hwheel_actions = g_slist_append(hwheel_actions, (char *) "REL_HWHEEL");
    hwheel_actions = g_slist_append(hwheel_actions, (char *) "REL_HWHEEL_HI_RES");

    gesture_actions = g_slist_append(gesture_actions, (char *) "KEY_LEFTALT");
    gesture_actions = g_slist_append(gesture_actions, (char *) "KEY_Z");

    l_device_set_name(device_conf, "Wireless Mouse MX Master 3");
    l_device_set_dpi(device_conf, 1700, 150, 6000, 100, true);
    l_device_set_smartshift(device_conf, false, 30, 50);
    l_device_set_hiresscroll(device_conf, true, false, false);
    l_device_append_button(device_conf, 0x52, KEYPRESS, middle_actions);
    l_device_append_button(device_conf, 0xc4, KEYPRESS, top_actions);
    l_device_append_button(device_conf, 0x56, KEYPRESS, forward_actions);
    l_device_append_button(device_conf, 0x53, KEYPRESS, back_actions);
    l_device_append_button(device_conf, 0xd7, KEYPRESS, hwheel_actions);
    l_device_append_button(device_conf, 0xc3, KEYPRESS, gesture_actions);
    l_device_reset_settings_state(device_conf);
}

static void
attach_buttons_conf(GSList *buttons_description, GSList *buttons_conf) {
    GSList *temp = buttons_description;

    while (temp != NULL) {
        ButtonDescription *description = temp->data;
        gpointer *conf = find_conf_cid(description->cid, buttons_conf);
        if (conf != NULL) {
            description->conf = conf;
        } else {
            set_default_button_conf(description->conf);
        }
        temp = g_slist_next(temp);
    }
}

static void
description_attach_conf(DeviceDescription *description, LDevice *device_conf) {
    GSList *buttons_conf = l_device_get_buttons_conf(device_conf);

    description->conf = device_conf;
    attach_buttons_conf(description->buttons, buttons_conf);
}

void
fill_description(DeviceDescription *description, LBusManager *bus, GString *device) {
    LDevice *device_conf = l_device_new();
    fill_device_conf(bus, device, device_conf);
    description_attach_conf(description, device_conf);
}

GSList *
l_data_manager_get_devices_list(LDataManager *self, GSList *descriptions_list) {
    GSList *sorted_list = NULL;
    GSList *devices = l_bus_manager_request_devices_list(self->bus_manager);
    GSList *temp = descriptions_list;

    while (temp != NULL) {
        GString *device;
        DeviceDescription *description = temp->data;

        device = find_device(self->bus_manager, devices,
                             description->full_name);
        if (device != NULL) {
            fill_description(description, self->bus_manager, device);
            sorted_list = g_slist_append(sorted_list, description);
        }

        temp = g_slist_next(temp);
    }
    return sorted_list;
}

LDataManager *
l_data_manager_new(void) {
    return g_object_new(L_TYPE_DATA_MANAGER, NULL);
}

static void
l_data_manager_class_init(LDataManagerClass *klass) {}

static void
l_data_manager_init(LDataManager *self) {
    self->bus_manager = l_bus_manager_new();
}
