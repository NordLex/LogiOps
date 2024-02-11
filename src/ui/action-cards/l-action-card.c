/* l-action-card.c
 *
 * Copyright 04.02.24 NordLex
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

#include "l-action-card.h"


G_DEFINE_INTERFACE(LActionCard, l_action_card, G_TYPE_OBJECT)

static void
l_action_card_default_init(LActionCardInterface *iface) {}

void
l_action_card_set_action(LActionCard *self, Action action) {
    LActionCardInterface *iface  = L_ACTION_CARD_GET_IFACE(self);
    iface->set_action(self, action);
}
