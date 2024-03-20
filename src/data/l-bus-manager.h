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

/**
 * @brief D-BUS manager constructor.
 * @return D-BUS manager instance.
 * */
LBusManager *
l_bus_manager_new(void);

/**
 * @brief Request device list from D-BUS.
 * @param [in] self D-BUS manager instance.
 * @return Devices paths list.
 * */
GSList *
l_bus_manager_request_devices_list(LBusManager *self);

/**
 * @brief Request device name.
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to device.
 * @return Device name string.
 * */
GString *
l_bus_manager_request_device_name(LBusManager *self,
                                  GString *device);

/**
 * @brief Request DPIs data.
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to device.
 * @param [out] dpi Pointer to a structure that will be filled with data.
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_dpi(LBusManager *self, GString *device, Dpi *dpi);

/**
 * @brief Request Hiresscroll data.
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to device.
 * @param [out] hiresscroll Pointer to a structure that will be filled with data.
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_hiresscroll(LBusManager *self, GString *device, Hiresscroll *hiresscroll);

/**
 * @brief Request SmartShift data.
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to device.
 * @param [out] smartshift Pointer to a structure that will be filled with data.
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_smartshift(LBusManager *self, GString *device, Smartshift *smartshift);

/**
 * @brief Request thumb wheel data.
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to the device.
 * @param [out] divert
 * @param [out] invert
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_thumb_wheel(LBusManager *self,
                                  GString *device,
                                  gboolean *divert,
                                  gboolean *invert);

/**
 * @brief Request buttons list
 * @param [in] self D-BUS manager instance.
 * @param [in] device Path to device.
 * @return Devices paths list.
 * */
GSList *
l_bus_manager_request_buttons_list(LBusManager *self,
                                   GString *device);

/**
 * @brief Request button info.
 * @param [in] self D-BUS manager instance.
 * @param [in] button Path to the button.
 * @param [out] cid Control ID.
 * @param [out] task_id
 * @param [out] gesture_support
 * @param [out] remappable
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_button_info(LBusManager *self,
                                  GString *button,
                                  guint16 *cid,
                                  guint16 *task_id,
                                  gboolean *gesture_support,
                                  gboolean *remappable);

/**
 * @brief Request button action.
 * @param [in] self D-BUS manager instance.
 * @param [in] button Path to the button.
 * @param [out] action Pointer to the action structure.
 * @return The execution status of the operation.
 * */
int
l_bus_manager_request_button_action(LBusManager *self,
                                    GString *button,
                                    Action *action);

/**
 * @brief Set keypress action.
 * @param [in] self D-BUS manager instance.
 * @param [in] button Path to the button.
 * @param [in] keypress Pointer to the keypress action structure.
 * @return The execution status of the operation.
 * */
int
l_bus_manager_set_keypress_action(LBusManager *self,
                                  GString *button,
                                  Keypress *keypress);

G_END_DECLS
