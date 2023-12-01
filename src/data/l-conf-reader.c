/* l-conf-reader.c
 *
 * Copyright 2023 NordLex
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

#include "l-conf-reader.h"

struct _LConfReader {
    GObject parent_instance;

    //config_t *cfg;
    LDevice *device;
};

G_DEFINE_FINAL_TYPE (LConfReader, l_conf_reader, G_TYPE_OBJECT)
/*
static void
l_conf_reader_read_conf_file(LConfReader *self, const char *file_name) {
    //config_read_file(self->cfg, file_name);
}*/

static void
l_conf_reader_init_device(LDevice *device) {
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

    l_device_set_name(device, "Wireless Mouse MX Master 3");
    l_device_set_dpi(device, 1700, 150, 6000, 100, true);
    l_device_set_smartshift(device, false, 30, 50);
    l_device_set_hiresscroll(device, true, false, false);
    l_device_append_button(device, 0x52, KEYPRESS, middle_actions);
    l_device_append_button(device, 0xc4, KEYPRESS, top_actions);
    l_device_append_button(device, 0x56, KEYPRESS, forward_actions);
    l_device_append_button(device, 0x53, KEYPRESS, back_actions);
    l_device_append_button(device, 0xd7, KEYPRESS, hwheel_actions);
    l_device_append_button(device, 0xc3, KEYPRESS, gesture_actions);
    l_device_reset_settings_state(device);
}

GObject *
l_conf_reader_get_device(LConfReader * self) {
    return G_OBJECT(self->device);
}

LConfReader *
l_conf_reader_new(const char *file_name) {
    LConfReader *conf_reader = g_object_new(L_TYPE_CONF_READER, NULL);

    //l_conf_reader_read(conf_reader, file_name);
    l_conf_reader_init_device(conf_reader->device);

    return conf_reader;
}

static void
l_conf_reader_class_init(LConfReaderClass *klass) {}

static void
l_conf_reader_init(LConfReader *self) {
    //config_init(self->cfg);
    self->device = l_device_new();
}