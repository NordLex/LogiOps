/* l-default-card.c
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

#include "l-default-card.h"

static void
action_card_interface_init(LActionCardInterface *iface);


struct _LDefaultCard {
    GtkBox parent_instance;
};

G_DEFINE_TYPE_WITH_CODE(LDefaultCard, l_default_card, GTK_TYPE_BOX,
                        G_IMPLEMENT_INTERFACE(L_TYPE_ACTION_CARD, action_card_interface_init))


static void
default_card_set_action(LActionCard *self, Action action) {
    //LDefaultCard *card = L_DEFAULT_CARD(self);
    g_print("== Default card set Action ==\n");
}

static void
action_card_interface_init(LActionCardInterface *iface) {
    iface->set_action = default_card_set_action;
}

LDefaultCard *
l_default_card_new(void) {
    return g_object_new(L_TYPE_DEFAULT_CARD, NULL);
}

static void
l_default_card_class_init(LDefaultCardClass *klass) {}

static void
l_default_card_init(LDefaultCard *self) {
    gtk_box_append(GTK_BOX(self), gtk_label_new("Default button functionality"));
}
