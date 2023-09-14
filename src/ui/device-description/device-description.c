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

ButtonDescription   scroll_wheel,
                    dpi_button,
                    horizontal_wheel,
                    copy_button,
                    paste_button,
                    gesture_button;

DeviceDescription   mx_master_3;

DeviceDescription * description_mx_master_3(void) {
    scroll_wheel.cid = 1;
    scroll_wheel.name = g_string_new("Scroll Wheel");
    scroll_wheel.x_offset = 0.62;
    scroll_wheel.y_offset = 0.21;

    dpi_button.cid = 2;
    dpi_button.name = g_string_new("DPI");
    dpi_button.x_offset = 0.68;
    dpi_button.y_offset = 0.37;

    horizontal_wheel.cid = 3;
    horizontal_wheel.name = g_string_new("Horizontal Wheel");
    horizontal_wheel.x_offset = 0.51;
    horizontal_wheel.y_offset = 0.45;

    copy_button.cid = 4;
    copy_button.name = g_string_new("Copy");
    copy_button.x_offset = 0.39;
    copy_button.y_offset = 0.45;

    paste_button.cid = 5;
    paste_button.name = g_string_new("Paste");
    paste_button.x_offset = 0.42;
    paste_button.y_offset = 0.545;

    gesture_button.cid = 6;
    gesture_button.name = g_string_new("Gestures");
    gesture_button.x_offset = 0.265;
    gesture_button.y_offset = 0.58;

    mx_master_3.name = g_string_new("MX Master 3");
    mx_master_3.image_path = g_string_new(MX_MASTER_3_IMAGE);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &scroll_wheel);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &dpi_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &horizontal_wheel);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &copy_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &paste_button);
    mx_master_3.buttons = g_slist_append(mx_master_3.buttons, &gesture_button);

    return &mx_master_3;
}
