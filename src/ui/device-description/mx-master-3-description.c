/* device-description.c
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

#include "device-description.h"

ButtonDescription   mas_scroll_wheel,
                    mas_dpi_button,
                    mas_horizontal_wheel,
                    mas_forward_button,
                    mas_back_button,
                    mas_gesture_button;

DeviceDescription   mx_master_3;

DeviceDescription *
description_mx_master_3(void) {
    mas_scroll_wheel.cid = 0x52;
    mas_scroll_wheel.name = g_string_new("Middle");
    mas_scroll_wheel.x_offset = 0.62;
    mas_scroll_wheel.y_offset = 0.21;

    mas_dpi_button.cid = 0xc4;
    mas_dpi_button.name = g_string_new("Mode Shift Button");
    mas_dpi_button.x_offset = 0.68;
    mas_dpi_button.y_offset = 0.37;

    mas_horizontal_wheel.cid = 0xd7;
    mas_horizontal_wheel.name = g_string_new("Thumb Wheel");
    mas_horizontal_wheel.x_offset = 0.51;
    mas_horizontal_wheel.y_offset = 0.45;

    mas_forward_button.cid = 0x56;
    mas_forward_button.name = g_string_new("Forward");
    mas_forward_button.x_offset = 0.39;
    mas_forward_button.y_offset = 0.45;

    mas_back_button.cid = 0x53;
    mas_back_button.name = g_string_new("Back");
    mas_back_button.x_offset = 0.42;
    mas_back_button.y_offset = 0.545;

    mas_gesture_button.cid = 0xc3;
    mas_gesture_button.name = g_string_new("Gesture Button");
    mas_gesture_button.x_offset = 0.265;
    mas_gesture_button.y_offset = 0.58;

    mx_master_3.name = g_string_new("MX Master 3");
    mx_master_3.full_name = g_string_new("Wireless Mouse MX Master 3");
    mx_master_3.image_path = g_string_new(MX_MASTER_3_IMAGE);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_scroll_wheel);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_dpi_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_horizontal_wheel);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_forward_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_back_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &mas_gesture_button);

    return &mx_master_3;
}
