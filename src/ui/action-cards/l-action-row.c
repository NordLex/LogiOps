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

    GListModel *list_model;
};

G_DEFINE_FINAL_TYPE (LActionRow, l_action_row, ADW_TYPE_COMBO_ROW)


static void
setup_list_item_cb(GtkListItemFactory *factory, GtkListItem *item) {
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(item, label);
}

static void
bind_list_item_cb(GtkListItemFactory *factory, GtkListItem *item) {
    GtkWidget *label = gtk_list_item_get_child(item);
    const char *name = gtk_list_item_get_item(item);

    gtk_label_set_text(GTK_LABEL(label), name);
    g_print("bind: %s\n", name);
}

static void
activate_cb(GtkListView *list, guint position, gpointer unused) {
    GtkWidget *label = g_list_model_get_item(G_LIST_MODEL(gtk_list_view_get_model(list)),
                                             position);

}

GListModel *
make_list_model(void) {
    GListModel *list_model;
    GtkListBoxRow *item_box;

    list_model = (GListModel *) gtk_string_list_new((const char *const *) action_names);

    return list_model;
}

void
l_action_row_set_selected(LActionRow *self, ActionType type) {
    adw_combo_row_set_selected(ADW_COMBO_ROW(self), type);
}

LActionRow *
l_action_row_new(void) {
    return g_object_new(L_TYPE_ACTION_ROW, NULL);
}

static void
l_action_row_class_init(LActionRowClass *klass) {}

static void
l_action_row_init(LActionRow *self) {
    char *subtitle = "Assign an self to the button";
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();


    self->list_model = make_list_model();
    /*list_view = gtk_list_view_new(
            GTK_SELECTION_MODEL(gtk_single_selection_new(self->list_model)),
            factory);*/

    g_signal_connect(factory, "setup", G_CALLBACK(setup_list_item_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_list_item_cb), NULL);

    g_object_set(self,
                 "title", "Action",
                 "subtitle", subtitle,
                 "model", self->list_model,
                 //"factory", factory,
                 NULL);

    //adw_combo_row_set_list_factory(ADW_COMBO_ROW(self), factory);
}