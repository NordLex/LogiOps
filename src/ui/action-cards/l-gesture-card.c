/* l-gesture-card.c
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
 
#include "l-gesture-card.h"


struct _LGestureCard {
    GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (LGestureCard, l_gesture_card, GTK_TYPE_BOX)

LGestureCard *
l_gesture_card_new(void) {
    return g_object_new(L_TYPE_GESTURE_CARD, NULL);
}

static void
l_gesture_card_class_init(LGestureCardClass *klass) {}

static void
l_gesture_card_init(LGestureCard *self) {}