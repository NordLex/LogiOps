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

#ifndef L_APPLICATION_RESOURCES
#define L_APPLICATION_RESOURCES

typedef enum  {
    KEYPRESS,
    GESTURES,
    TOGGLE_SMARTSHIFT,
    CYCLE_DPI,
} ActionType;


#include <adwaita.h>
#include "types/description-types.h"
#include "types/l-device.h"
#include "ui/device-description/device-description.h"
#include "ui/l-device-card.h"
#include "ui/action-cards/l-keypress-card.h"
#include "ui/action-cards/l-gesture-card.h"
#include "ui/l-overview-page.h"
#include "ui/l-device-page.h"
#include "ui/l-device-button.h"
#include "ui/l-button-pref-panel.h"
#include "ui/l-pref-panel.h"
#include "data/l-key-codes.h"
#include "data/l-data-manager.h"
#include "data/l-bus-manager.h"

#define L_APP_ID                "org.nordlex.logiops"
#define L_APP_NAME              "LogiOps"
#define L_CSS_STYLE_PATH        "/org/nordlex/logiops/resources/media/application_style.css"

#define MX_MASTER_3_IMAGE           "/org/nordlex/logiops/resources/media/mx-master-3.png"
#define MX_MASTER_3_IMAGE_LIGHT     "/org/nordlex/logiops/resources/media/mx-master-3-light..."
#define MX_ANYWHERE_3_IMAGE         "/org/nordlex/logiops/resources/media/mx-anywhere-3.png"
#define MX_ANYWHERE_3_IMAGE_LIGHT   "/org/nordlex/logiops/resources/media/mx-anywhere-3-light..."

#define L_DEVICE_BUTTON_SIZE    45

#define L_BATTERY_0             "/org/nordlex/logiops/resources/media/battery/0.svg"
#define L_BATTERY_20            "/org/nordlex/logiops/resources/media/battery/20.svg"
#define L_BATTERY_50            "/org/nordlex/logiops/resources/media/battery/50.svg"
#define L_BATTERY_80            "/org/nordlex/logiops/resources/media/battery/80.svg"
#define L_BATTERY_100           "/org/nordlex/logiops/resources/media/battery/100.svg"

extern const char *frame[1];

#define SET_FRAME(widget) (gtk_widget_set_css_classes(widget, frame))

#endif