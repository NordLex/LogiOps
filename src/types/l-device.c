/* l-device.c
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

#include "l-device.h"

struct _LDevice {
    GObject parent_instance;

    GString *name;
    gint dpi;
    GSList *buttons;
};

G_DEFINE_FINAL_TYPE (LDevice, l_device, G_TYPE_OBJECT)

GString *
l_device_get_name(LDevice *self) {
    return self->name;
}

static void
l_device_buttons_fill(GSList *buttons) {
    gpointer data = NULL;
    g_slist_append(buttons, data);
}

LDevice *
l_device_new(const char *name) {
    LDevice *device = g_object_new(L_TYPE_DEVICE, NULL);
    device->name = g_string_new(name);
    l_device_buttons_fill(device->buttons);

    return device;
}

static void
l_device_class_init(LDeviceClass *klass) {}

static void
l_device_init(LDevice *self) {}