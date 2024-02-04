/* l-action-selector.c
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

#include "l-action-selector.h"


struct _LActionSelector {
    GtkBox parent_instance;

    GtkWidget *selector;
};

G_DEFINE_FINAL_TYPE(LActionSelector, l_action_selector, GTK_TYPE_BOX)


static void
callback(GtkDropDown *self, gpointer data) {
    guint item = gtk_drop_down_get_selected(self);
    g_print("== Selected %d ==\n", item);
}

void
l_action_selector_set_selected(GtkWidget *self, ActionType type) {
    LActionSelector *main = L_ACTION_SELECTOR(self);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(main->selector), type);
}

GtkWidget *
l_action_selector_new(void) {
    return g_object_new(L_TYPE_ACTION_SELECTOR, NULL);
}

static void
l_action_selector_class_init(LActionSelectorClass *klass) {}

static void
l_action_selector_init(LActionSelector *self) {
    int margin = 20;
    self->selector = gtk_drop_down_new_from_strings((const char *const *) action_names);

    g_object_set(self,
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 NULL);

    gtk_widget_set_margin_start(GTK_WIDGET(self), margin);
    gtk_widget_set_margin_end(GTK_WIDGET(self), margin);
    gtk_widget_set_margin_bottom(GTK_WIDGET(self), (int) (margin * 0.5));
    gtk_box_append(GTK_BOX(self), self->selector);

    g_signal_connect(self->selector, "activate", G_CALLBACK(callback), NULL);
}
