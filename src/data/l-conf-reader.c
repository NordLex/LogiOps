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

static void
l_conf_reader_read_conf_file(LConfReader *self, const char *file_name) {
    //config_read_file(self->cfg, file_name);
}

void
l_conf_reader_init_device(LDevice *device) {
    GSList *one_actions = NULL;
    GSList *two_actions = NULL;

    one_actions = g_slist_append(one_actions, "KEY_CTRL");
    one_actions = g_slist_append(one_actions, "KEY_L");

    two_actions = g_slist_append(two_actions, "KEY_ALT");
    two_actions = g_slist_append(two_actions, "KEY_Z");

    l_device_set_name(device, "MX Master 3");
    l_device_set_dpi(device, 1700);
    l_device_set_smartshift(device, false, 30, 50);
    l_device_set_hiresscroll(device, true, false, false);
    l_device_append_button(device, 0xc2, KEYPRESS, one_actions);
    l_device_append_button(device, 0xc3, KEYPRESS, one_actions);
    l_device_append_button(device, 0xc4, KEYPRESS, two_actions);
    l_device_append_button(device, 0xc5, KEYPRESS, one_actions);
    l_device_append_button(device, 0xc6, KEYPRESS, two_actions);
    l_device_append_button(device, 0xc7, KEYPRESS, one_actions);
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