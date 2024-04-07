/* l-keypress-card.h
 *
 * Copyright 24.01.2024 NordLex
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

#define L_TYPE_KEYPRESS_CARD (l_keypress_card_get_type())

G_DECLARE_FINAL_TYPE(LKeypressCard, l_keypress_card, L, KEYPRESS_CARD, GtkButton)

LKeypressCard *
l_keypress_card_new(GtkWindow *key_grab_window);

G_END_DECLS
