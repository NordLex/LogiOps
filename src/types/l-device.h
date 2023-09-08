/* l-device.h
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

#define L_TYPE_DEVICE (l_device_get_type())

G_DECLARE_FINAL_TYPE (LDevice, l_device, L, DEVICE, GObject)

typedef struct {
    gboolean on;
    gint threshold;
    gint torque;
} Smartshift;

typedef struct {
    gboolean hires;
    gboolean invert;
    gboolean target;
} Hiresscroll;

typedef struct {
    ActionType type;
    GSList *keys;
} Action;

typedef struct {
    GString direction;
    GString mode;
    Action action;
} Gesture;

typedef struct {
    gint cid;
    Gesture gesture;
    Action action;
} Button;

gboolean
l_device_settings_is_changed(LDevice *self);

void
l_device_reset_settings_state(LDevice *self);

LDevice *
l_device_new(void);

GString *
l_device_get_name(LDevice *self);

gint *
l_device_get_dpi(LDevice *self);

Smartshift *
l_device_get_smartshift(LDevice *self);

Hiresscroll *
l_device_get_hiresscroll(LDevice *self);

gboolean
l_device_get_smartshift_state(LDevice *self);

gint
l_device_get_smartshift_threshold(LDevice *self);

gint
l_device_get_smartshift_torque(LDevice *self);

gboolean
l_device_get_hiresscroll_hires(LDevice *self);

gboolean
l_device_get_hiresscroll_invert(LDevice *self);

gboolean
l_device_get_hiresscroll_target(LDevice *self);

void
l_device_set_name(LDevice *self, const char *name);

void
l_device_set_dpi(LDevice *self, gint dpi);

void
l_device_set_smartshift(LDevice *self, gboolean on, gint threshold, gint torque);

void
l_device_set_hiresscroll(LDevice *self, gboolean hires, gboolean invert, gboolean target);

void
l_device_append_button(LDevice *self, gint sid, ActionType action_type, GSList *action_keys);

G_END_DECLS
