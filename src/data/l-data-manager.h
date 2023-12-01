/* l-data-manager.h
 *
 * Copyright 10.11.2023 NordLex
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

#define L_TYPE_DATA_MANAGER (l_data_manager_get_type())

G_DECLARE_FINAL_TYPE(LDataManager, l_data_manager, L, DATA_MANAGER, GObject)

LDataManager *
l_data_manager_new(void);

GSList *
l_data_manager_get_devices_list(LDataManager *self, GSList *descriptions_list);

G_END_DECLS
