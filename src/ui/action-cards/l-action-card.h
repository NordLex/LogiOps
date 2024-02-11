/* l-action-card.h
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

#pragma once

#include "../../l-application-resources.h"

G_BEGIN_DECLS

#define L_TYPE_ACTION_CARD l_action_card_get_type()

G_DECLARE_INTERFACE(LActionCard, l_action_card, L, ACTION_CARD, GObject)

struct _LActionCardInterface {
    GTypeInstance *parent;

    void (*set_action) (LActionCard *, Action);
};

void
l_action_card_set_action(LActionCard *self, Action action);

G_END_DECLS