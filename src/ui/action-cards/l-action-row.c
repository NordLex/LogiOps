/* l-action-row.c
 *
 * Copyright 27.01.2024 NordLex
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
 
#include "l-action-row.h"


struct _LActionRow {
    AdwComboRow parent_instance;

    GtkListItemFactory *list_box;
};

G_DEFINE_FINAL_TYPE (LActionRow, l_action_row, ADW_TYPE_COMBO_ROW)

void
l_action_row_set_data(LActionRow *self, Button *button) {

}

LActionRow *
l_action_row_new(void) {
    return g_object_new(L_TYPE_ACTION_ROW, NULL);
}

static void
l_action_row_class_init(LActionRowClass *klass) {}

static void
l_action_row_init(LActionRow *self) {
    self->list_box = adw_combo_row_get_factory(ADW_COMBO_ROW(self));

    g_object_set(self,
                 "title", "Action",
                 "subtitle", "Will be executed when pressed",
                 NULL);
}