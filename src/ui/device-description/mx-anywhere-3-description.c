/* mx-anywhere-3-description.c
 *
 * Copyright 22.09.2023 nordlex
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

ButtonDescription   any_scroll_wheel,
                    any_dpi_button,
                    any_forward_button,
                    any_back_button;

DeviceDescription mx_anywhere_3;

DeviceDescription *
description_mx_anywhere_3(void) {
    any_scroll_wheel.cid = 0x52;
    any_scroll_wheel.name = g_string_new("Middle");
    any_scroll_wheel.x_offset = 0.61;
    any_scroll_wheel.y_offset = 0.21;

    any_dpi_button.cid = 0xc4;
    any_dpi_button.name = g_string_new("Mode Shift Button");
    any_dpi_button.x_offset = 0.65;
    any_dpi_button.y_offset = 0.36;

    any_forward_button.cid = 0x56;
    any_forward_button.name = g_string_new("Forward");
    any_forward_button.x_offset = 0.34;
    any_forward_button.y_offset = 0.46;

    any_back_button.cid = 0x53;
    any_back_button.name = g_string_new("Back");
    any_back_button.x_offset = 0.36;
    any_back_button.y_offset = 0.59;

    mx_anywhere_3.name = g_string_new("MX Anywhere 3");
    mx_anywhere_3.full_name = g_string_new("MX Anywhere 3");
    mx_anywhere_3.image_path = g_string_new(MX_ANYWHERE_3_IMAGE);
    mx_anywhere_3.buttons = g_slist_append(mx_anywhere_3.buttons, &any_scroll_wheel);
    mx_anywhere_3.buttons = g_slist_append(mx_anywhere_3.buttons, &any_dpi_button);
    mx_anywhere_3.buttons = g_slist_append(mx_anywhere_3.buttons, &any_forward_button);
    mx_anywhere_3.buttons = g_slist_append(mx_anywhere_3.buttons, &any_back_button);
    return &mx_anywhere_3;
}