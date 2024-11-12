/* l-signal-processor.h
 *
 * Copyright 03.11.2024 NordLex
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

#include "l-application-resources.h"


G_BEGIN_DECLS

#define L_TYPE_SAVER (l_saver_get_type())

G_DECLARE_FINAL_TYPE(LSaver, l_saver, L, SAVER, GObject)

void
l_saver_set_dpi(LSaver *self, GString *name, gint dpi);

void
l_saver_set_hires(LSaver *self, GString *name, gboolean hires);

void
l_saver_set_invert(LSaver *self, GString *name, gboolean invert);

void
l_saver_set_target(LSaver *self, GString *name, gboolean target);

void
l_saver_set_sm_state(LSaver *self, GString *name, gboolean state);

void
l_saver_set_sm_threshold(LSaver *self, GString *name, gint value);

void
l_saver_set_sm_torque(LSaver *self, GString *name, gint value);

LSaver *
l_saver_new(void);

G_END_DECLS
