/* l-device-button.c
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

#include "l-device-button.h"


struct _LDeviceButton {
    GtkButton parent_instance;

    offset_t offset;
};

G_DEFINE_FINAL_TYPE (LDeviceButton, l_device_button, GTK_TYPE_BUTTON)

offset_t * l_device_button_get_offset(LDeviceButton * self) {
    return &self->offset;
}

LDeviceButton * l_device_button_new(gdouble x_offset, gdouble y_offset, GCallback callback, gpointer data) {
    LDeviceButton * object = g_object_new(L_TYPE_DEVICE_BUTTON, NULL);

    object->offset.x = x_offset;
    object->offset.y = y_offset;

    g_signal_connect(G_OBJECT(object), "clicked", callback, data);

    return object;
}

static void l_device_button_class_init(LDeviceButtonClass * klass) {}

static void l_device_button_init(LDeviceButton * self) {
    gtk_widget_set_size_request(GTK_WIDGET(self),
                                L_DEVICE_BUTTON_SIZE,
                                L_DEVICE_BUTTON_SIZE);

    g_object_set(self,
                 "name", "DeviceButton",
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_START,
                 NULL);
}