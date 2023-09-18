/* l-pref-panel.h
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

G_BEGIN_DECLS

#define L_TYPE_PREF_PANEL (l_pref_panel_get_type())

G_DECLARE_FINAL_TYPE (LPrefPanel, l_pref_panel, L, PREF_PANEL, GtkBox)

LPrefPanel *
l_pref_panel_new(void);

void
l_pref_panel_configure(LPrefPanel * self, gpointer device_conf);

void
l_pref_panel_centered(LPrefPanel *self, int width);

void
l_pref_panel_expand(LPrefPanel *self);

G_END_DECLS