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
    AdwExpanderRow parent_instance;

    GtkWidget *label;
    GtkWidget *check_button;
    GtkWidget *child;
};

G_DEFINE_FINAL_TYPE (LActionRow, l_action_row, ADW_TYPE_EXPANDER_ROW)


void
sync_expand(GtkCheckButton *check_button, gpointer data) {
    LActionRow *self = L_ACTION_ROW(data);
    gboolean state = gtk_check_button_get_active(check_button);
    if (state)
        adw_expander_row_set_enable_expansion(ADW_EXPANDER_ROW(self), TRUE);
    else
        adw_expander_row_set_enable_expansion(ADW_EXPANDER_ROW(self), FALSE);
}

GtkCheckButton *
l_action_row_get_check_button(LActionRow *self) {
    return GTK_CHECK_BUTTON(self->check_button);
}

void
l_action_row_set_data(LActionRow *self, Button *button) {
    gtk_label_set_label(GTK_LABEL(self->label), "Keypress"); 
    l_keypress_card_set_data(L_KEYPRESS_CARD(self->child), button->action.keys);
}

LActionRow *
l_action_row_new(void) {
    return g_object_new(L_TYPE_ACTION_ROW, NULL);
}

static void
l_action_row_class_init(LActionRowClass *klass) {}

static void
l_action_row_init(LActionRow *self) {
    self->label = gtk_label_new("");
    self->check_button = gtk_check_button_new();
    self->child = GTK_WIDGET(l_keypress_card_new());

    adw_expander_row_add_prefix(ADW_EXPANDER_ROW(self), self->check_button);
    adw_expander_row_add_prefix(ADW_EXPANDER_ROW(self), self->label);
    adw_expander_row_add_row(ADW_EXPANDER_ROW(self), self->child);

    sync_expand(GTK_CHECK_BUTTON(self->check_button), self);
    g_signal_connect(self->check_button, "toggled", G_CALLBACK(sync_expand), self);
}