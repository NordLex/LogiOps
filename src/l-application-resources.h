/* l-application-resource.h
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

#ifndef APPLICATION_RESOURCES_H
#define APPLICATION_RESOURCES_H

#include <adwaita.h>
#include "ui/l-device-button.h"

#define L_APP_ID           "org.nordlex.logiops"
#define L_APP_NAME         "Logi::Ops"
#define L_CSS_STYLE_PATH   "/org/nordlex/logiops/resources/media/application_style.css"
#define L_DEVICE_IMAGE     "/org/nordlex/logiops/resources/media/mx_master_3.png"
#define L_DEVICE_BUTTON_SIZE 42


extern const char * frame[1];

#define SET_FRAME(widget) (gtk_widget_set_css_classes(widget, frame))

#endif