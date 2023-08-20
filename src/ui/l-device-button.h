/* l-device-button.h
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

#pragma once

#include "../l-application-resources.h"

typedef struct {
    gdouble x;
    gdouble y;
} offset_t;

G_BEGIN_DECLS

#define L_TYPE_DEVICE_BUTTON (l_device_button_get_type())

G_DECLARE_FINAL_TYPE (LDeviceButton, l_device_button, L, DEVICE_BUTTON, GtkButton)

LDeviceButton * l_device_button_new(gdouble x_offset, gdouble y_offset, GCallback callback, gpointer data);

offset_t * l_device_button_get_offset(LDeviceButton * self);

G_END_DECLS
