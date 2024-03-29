/* l-key-code.h
 *
 * Copyright 26.02.24 NordLex
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

#define L_TYPE_KEY_CODE (l_key_code_get_type())

G_DECLARE_FINAL_TYPE(LKeyCode, l_key_code, L, KEY_CODE, GObject)

/**
 * @brief Converted Kernel key code to GDK key code.
 * @param [in] self Converter instance.
 * @param [in] key Kernel key code.
 * @return Pointer to GDK key code (guint). Returned NULL if not found.
 * */
void *
l_key_code_kernel_to_gdk(LKeyCode *self, char *key);

/**
 * @brief Converted GDK key cod to Kernel key code.
 * @param [in] self Converter instance.
 * @param [in] key GDK key code.
 * @return Pointer to Kernel key code (char**). Returned NULL if not found.
 * */
void *
l_key_code_gdk_to_kernel(LKeyCode *self, guint key);

/**
 * @brief Key codes converter.
 * @return Converter instance.
 * */
LKeyCode *
l_key_code_new(void);

G_END_DECLS
