/* description-types.h
 *
 * Copyright 22.09.2023 nordlex
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

/**
 * @struct [dpi] Mouse sensor resolution.
 * @struct [min] Minimal sensor resolution.
 * @struct [max] Maximal sensor resolution.
 * @struct [step] DPI change step.
 * @struct [range]
 * */
typedef struct {
    gint        dpi;
    gint        min;
    gint        max;
    gint        step;
    gboolean    range;
} Dpi;

/**
 *@struct [torque_support] Support of configure torque.
 *@struct [on] On/Off switch SmartShift.
 *@struct [threshold] Response threshold.
 *@struct [torque] Scroll resistance.
 * */
typedef struct {
    gboolean    torque_support;
    gboolean    on;
    gint        threshold;
    gint        torque;
} Smartshift;

/**
 * @struct [hires] Field that defines whether the mouse wheel should be high resolution or not.
 * @struct [invert] Field that defines whether to invert the mouse wheel.
 * @struct [target] "true" for HID++ notification, "false" for normal usage.
 * */
typedef struct {
    gboolean    hires;
    gboolean    invert;
    gboolean    target;
} Hiresscroll;

/**
 * @struct [type] Action type.
 * @struct [self] Pointer to action struct.
 * */
typedef struct {
    ActionType  type;
    gpointer    self;
} Action;

/**
 * @struct [*keys] Keycode list.
 * */
typedef struct {
    GSList     *keys;
} Keypress;

/**
 * @struct [threshold] Optional integer field that determines the number of pixels
 * at which a gesture should activate.
 * @struct [mode] This field defaults to OnRelease if it is omitted.
 * @struct [no_press] The action field is ignored when this mode is used.
 * This gesture is compatible with scroll wheels.
 * @struct [action_up] Mandatory field that defines the action the gesture uses.
 * This can be any action other than Gestures.
 * @struct [action_down] See above.
 * @struct [action_left] See above.
 * @struct [action_right] See above.
 * */
typedef struct {
    guint       threshold;  // Optional
    GString     mode;       // Optional
    gboolean    no_press;
    Action      action_up;
    Action      action_down;
    Action      action_left;
    Action      action_right;
} Gesture;

/**
 * @struct [sensor] Optional field that will determine what sensor the DPI will switch on.
 * @struct [*dpis] Mandatory integer array field that defines what DPIs to cycle through.
 * (e.g. dpis: [800, 1000, 1200];).
 * */
typedef struct {
    guint       sensor;     // Optional
    GSList     *dpis;
} CycleDPI;

/**
 * This action toggles the SmartShift scrolling feature when pressed.
 * There are no additional fields.
 * */
typedef struct {} ToggleSmartShift;

/**
 * This action toggles high resolution scrolling when pressed.
 * There are no additional fields.
 * */
typedef struct {} ToggleHiresScroll;

/**
 * @struct [sensor] Optional field that will determine what sensor the DPI will switch on.
 * @struct [*inc] This is an integer array field that defines what to increase the DPI by.
 * */
typedef struct {
    guint       sensor;     // Optional
    guint      *inc;
} ChangeDPI;

/**
 * @struct [host] This field may either be an integer representing the host number
 * (one-indexed, as shown on the bottom of the mouse), "next" to go to the next host number,
 * or "prev"/"previous" to go to the previous host number. (e.g. host = 2; or host = "next";).
 * */
typedef struct {
    guint       host;
} ChangeHost;

/**
 * @struct [cid] Control ID
 * @struct [task_id]
 * @struct [gesture_support] An immutable property indicating whether the button supports gestures.
 * @struct [remappable] An immutable property indicating whether the button supports assigning actions.
 * @struct [action] Action struct.
 * */
typedef struct {
    gint        cid;
    gint        task_id;
    gboolean    gesture_support;
    gboolean    remappable;
    Action      action;
} Button;

/**
 * Button description
 *
 * @struct [cid] Control ID.
 * @struct [*name] Name of button.
 * @struct [x_offset] Offset from center.
 * @struct [y_offset] Offset from center.
 * @struct [conf] Pointer to Struct Button.
 * */
typedef struct {
    gint        cid;
    GString    *name;
    gdouble     x_offset;
    gdouble     y_offset;
    gpointer    conf;
} ButtonDescription;

/**
 * Device description
 *
 * @struct [*name] Device name (used for UI).
 * @struct [*full_name] Device name (used for communication via D_BUSS).
 * @struct [*image_path] Device image path.
 * @struct [*buttons] List of buttons description.
 * @struct [conf] Pointer to Class Device.
 */
typedef struct {
    GString    *name;
    GString    *full_name;
    GString    *image_path;
    GSList     *buttons;
    gpointer    conf;
} DeviceDescription;
