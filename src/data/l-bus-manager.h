/* l-bus-manager.h
 *
 * Copyright 25.09.2023 NordLex
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

#define L_TYPE_BUS_MANAGER (l_bus_manager_get_type())

G_DECLARE_FINAL_TYPE(LBusManager, l_bus_manager, L, BUS_MANAGER, GObject)

LBusManager *
l_bus_manager_new(void);

GSList *
l_bus_manager_request_devices_list(LBusManager *self);

GString *
l_bus_manager_request_device_name(LBusManager *self,
                                  GString *device);

int
l_bus_manager_request_dpi(LBusManager *self,
                          GString *device,
                          guint16 *dpi,
                          guint16 *dpi_step,
                          guint16 *dpi_min,
                          guint16 *dpi_max,
                          gboolean *range);

int
l_bus_manager_request_hiresscroll(LBusManager *self,
                                  GString *device,
                                  gboolean *hires,
                                  gboolean *invert,
                                  gboolean *target);

int
l_bus_manager_request_smartshift(LBusManager *self,
                                 GString *device,
                                 gboolean *torque_support,
                                 guchar *active,
                                 guchar *threshold,
                                 guchar *torque);

int
l_bus_manager_request_thumb_wheel(LBusManager *self,
                                  GString *device,
                                  gboolean *divert,
                                  gboolean *invert);

GSList *
l_bus_manager_request_buttons_list(LBusManager *self,
                                   GString *device);

int
l_bus_manager_request_button_info(LBusManager *self,
                                  GString *button,
                                  guint16 *cid,
                                  guint16 *task_id);

G_END_DECLS
