/* l-key-grab-window.c
 *
 * Copyright 02.04.24 NordLex
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

#include "l-key-grab-window.h"


struct _LKeyGrabWindow {
    GObject parent_instance;
};

G_DEFINE_FINAL_TYPE(LKeyGrabWindow, l_key_grab_window, ADW_TYPE_WINDOW)

LKeyGrabWindow *
l_key_grab_window_new(GtkWindow *parent) {
    LKeyGrabWindow *self = g_object_new(L_TYPE_KEY_GRAB_WINDOW, NULL);

    

    return self;
}

static void
l_key_grab_window_class_init(LKeyGrabWindowClass *klass) {}

static void
l_key_grab_window_init(LKeyGrabWindow *self) {}
