/* l-device.c
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

#include "l-device.h"

struct _LDevice {
    GObject parent_instance;

    GString *name;
    gboolean settings_is_changed;
    Dpi dpi;
    Smartshift *smartshift;
    Hiresscroll *hiresscroll;
    GSList *buttons;
};

G_DEFINE_FINAL_TYPE (LDevice, l_device, G_TYPE_OBJECT)

gboolean
l_device_settings_is_changed(LDevice *self) {
    return self->settings_is_changed;
}

void
l_device_reset_settings_state(LDevice *self) {
    self->settings_is_changed = FALSE;
}

GString *
l_device_get_name(LDevice *self) {
    return self->name;
}

Dpi *
l_device_get_dpi(LDevice *self) {
    return &self->dpi;
}

/**  Smartshift  */
gboolean
l_device_get_smartshift_state(LDevice *self) {
    return self->smartshift->on;
}

gint
l_device_get_smartshift_threshold(LDevice *self) {
    return self->smartshift->threshold;
}

gint
l_device_get_smartshift_torque(LDevice *self) {
    return self->smartshift->torque;
}

Smartshift *
l_device_get_smartshift(LDevice *self) {
    return self->smartshift;
}

void
l_device_set_smartshift(LDevice *self, gboolean on, gint threshold, gint torque) {
    self->smartshift->on = on;
    self->smartshift->threshold = threshold;
    self->smartshift->torque = torque;
    self->settings_is_changed = TRUE;
}

/**  Hiresscroll */
gboolean
l_device_get_hiresscroll_hires(LDevice *self) {
    return self->hiresscroll->hires;
}

gboolean
l_device_get_hiresscroll_invert(LDevice *self) {
    return self->hiresscroll->invert;
}

gboolean
l_device_get_hiresscroll_target(LDevice *self) {
    return self->hiresscroll->target;
}

Hiresscroll *
l_device_get_hiresscroll(LDevice *self) {
    return self->hiresscroll;
}

void
l_device_set_hiresscroll(LDevice *self, gboolean hires, gboolean invert, gboolean target) {
    self->hiresscroll->hires = hires;
    self->hiresscroll->invert = invert;
    self->hiresscroll->target = target;
    self->settings_is_changed = TRUE;
}

/**
 * Name
 **/
void
l_device_set_name(LDevice *self, const char *name) {
    self->name = g_string_new(name);
    self->settings_is_changed = TRUE;
}

/**
 * DPI
 **/
void
l_device_set_dpi(LDevice *self, gint dpi, gint min, gint max, gint step, gboolean range) {
    self->dpi.dpi = dpi;
    self->dpi.min = min;
    self->dpi.max = max;
    self->dpi.step = step;
    self->dpi.range = range;
    self->settings_is_changed = TRUE;
}

/**
 * Button configuration
 **/
void
l_device_append_button(LDevice *self, gint cid, ActionType action_type, GSList *action_keys) {
    Button *button = g_malloc(sizeof(Button));

    button->cid = cid;
    button->action.type = action_type;
    button->action.keys = action_keys;

    self->buttons = g_slist_append(self->buttons, button);
}

GSList *
l_device_get_buttons_conf(LDevice *self) {
    return self->buttons;
}

LDevice *
l_device_new(void) {
    return g_object_new(L_TYPE_DEVICE, NULL);
}

static void
l_device_class_init(LDeviceClass *klass) {}

static void
l_device_init(LDevice *self) {
    self->name = g_malloc(sizeof(GString));
    self->settings_is_changed = FALSE;
    self->smartshift = g_malloc(sizeof(Smartshift));
    self->hiresscroll = g_malloc(sizeof(Hiresscroll));
}