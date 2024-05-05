/* l-key-label.h
 *
 * Copyright 18.04.24 NordLex
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

#include <libadwaita-1/adwaita.h>


G_BEGIN_DECLS

#define L_TYPE_KEYS_LABEL (l_keys_label_get_type())

G_DECLARE_FINAL_TYPE(LKeysLabel, l_keys_label, L, KEYS_LABEL, GtkBox)

LKeysLabel *
l_keys_label_new(GSList *key_codes);

G_END_DECLS
