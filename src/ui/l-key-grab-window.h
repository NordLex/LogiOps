/* l-key-grab-window.h
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

#pragma once

#include "../l-application-resources.h"


G_BEGIN_DECLS

#define L_TYPE_KEY_GRAB_WINDOW (l_key_grab_window_get_type())

G_DECLARE_FINAL_TYPE(LKeyGrabWindow, l_key_grab_window, L, KEY_GRAB_WINDOW, AdwWindow)

LKeyGrabWindow *
l_key_grab_window_new(void);

void
l_key_grab_window_set_parent(LKeyGrabWindow *self, GtkWindow *parent);

GSList*
l_key_grab_window_get_keys(LKeyGrabWindow *self);

G_END_DECLS
