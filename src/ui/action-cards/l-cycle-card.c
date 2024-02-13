/* l-cycle-card.c
 *
 * Copyright 11.02.24 NordLex
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

#include "l-cycle-card.h"

static void
action_card_interface_init(LActionCardInterface *iface);


struct _LCycleCard {
    GtkBox parent_instance;
};

G_DEFINE_TYPE_WITH_CODE(LCycleCard, l_cycle_card, GTK_TYPE_BOX,
                        G_IMPLEMENT_INTERFACE(L_TYPE_ACTION_CARD, action_card_interface_init))


static void
cycle_card_set_action(LActionCard *self, Action action) {
    g_print("=Cycle DPI=\n");
}

static void
action_card_interface_init(LActionCardInterface *iface) {
    iface->set_action = cycle_card_set_action;
}

LCycleCard *
l_cycle_card_new(void) {
    return g_object_new(L_TYPE_CYCLE_CARD, NULL);
}

static void
l_cycle_card_class_init(LCycleCardClass *klass) {}

static void
l_cycle_card_init(LCycleCard *self) {
    gtk_box_append(GTK_BOX(self), gtk_label_new("Cycle DPI"));
}
