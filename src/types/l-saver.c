/* l-signal-processor.c
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

#include "l-saver.h"


static guint signal_set_dpi;
static guint signal_set_hires;
static guint signal_set_invert;
static guint signal_set_target;
static guint signal_set_sm_state;
static guint signal_set_sm_threshold;
static guint signal_set_sm_torque;

struct _LSaver {
    GObject parent_instance;
};

G_DEFINE_FINAL_TYPE(LSaver, l_saver, G_TYPE_OBJECT)


void
l_saver_set_dpi(LSaver *self, GString *name, gint dpi) {
    g_signal_emit(self, signal_set_dpi, 0, name, dpi);
}

void
l_saver_set_hires(LSaver *self, GString *name, gboolean hires) {
    g_signal_emit(self, signal_set_hires, 0, name, hires);
}

void
l_saver_set_invert(LSaver *self, GString *name, gboolean invert) {
    g_signal_emit(self, signal_set_invert, 0, name, invert);
}

void
l_saver_set_target(LSaver *self, GString *name, gboolean target) {
    g_signal_emit(self, signal_set_target, 0, name, target);
}

void
l_saver_set_sm_state(LSaver *self, GString *name, gboolean state) {
    g_signal_emit(self, signal_set_sm_state, 0, name, state);
}

void
l_saver_set_sm_threshold(LSaver *self, GString *name, gint value) {
    g_signal_emit(self, signal_set_sm_threshold, 0, name, value);
}

void
l_saver_set_sm_torque(LSaver *self, GString *name, gint value) {
    g_signal_emit(self, signal_set_sm_torque, 0, name, value);
}

LSaver *
l_saver_new(void) {
    return g_object_new(L_TYPE_SAVER, NULL);
}

static void
l_saver_class_init(LSaverClass *klass) {
    signal_set_dpi = g_signal_new("set-dpi",
                                  G_TYPE_FROM_CLASS(klass),
                                  G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                  0,
                                  NULL,
                                  NULL,
                                  NULL,
                                  G_TYPE_NONE,
                                  2,
                                  G_TYPE_STRING,
                                  G_TYPE_INT,
                                  NULL);
    signal_set_hires = g_signal_new("set-hires",
                                    G_TYPE_FROM_CLASS(klass),
                                    G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                    0,
                                    NULL,
                                    NULL,
                                    NULL,
                                    G_TYPE_NONE,
                                    2,
                                    G_TYPE_STRING,
                                    G_TYPE_BOOLEAN,
                                    NULL);
    signal_set_invert = g_signal_new("set-invert",
                                     G_TYPE_FROM_CLASS(klass),
                                     G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                     0,
                                     NULL,
                                     NULL,
                                     NULL,
                                     G_TYPE_NONE,
                                     2,
                                     G_TYPE_STRING,
                                     G_TYPE_BOOLEAN,
                                     NULL);
    signal_set_target = g_signal_new("set-target",
                                     G_TYPE_FROM_CLASS(klass),
                                     G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                     0,
                                     NULL,
                                     NULL,
                                     NULL,
                                     G_TYPE_NONE,
                                     2,
                                     G_TYPE_STRING,
                                     G_TYPE_BOOLEAN,
                                     NULL);
    signal_set_sm_state = g_signal_new("set-smartshift-state",
                                       G_TYPE_FROM_CLASS(klass),
                                       G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                       0,
                                       NULL,
                                       NULL,
                                       NULL,
                                       G_TYPE_NONE,
                                       2,
                                       G_TYPE_STRING,
                                       G_TYPE_BOOLEAN,
                                       NULL);
    signal_set_sm_threshold = g_signal_new("set-smartshift-threshold",
                                           G_TYPE_FROM_CLASS(klass),
                                           G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                           0,
                                           NULL,
                                           NULL,
                                           NULL,
                                           G_TYPE_NONE,
                                           2,
                                           G_TYPE_STRING,
                                           G_TYPE_INT,
                                           NULL);
    signal_set_sm_torque = g_signal_new("set-smartshift-torque",
                                        G_TYPE_FROM_CLASS(klass),
                                        G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                        0,
                                        NULL,
                                        NULL,
                                        NULL,
                                        G_TYPE_NONE,
                                        2,
                                        G_TYPE_STRING,
                                        G_TYPE_INT,
                                        NULL);

}

static void
l_saver_init(LSaver *self) {}
