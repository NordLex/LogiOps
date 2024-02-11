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
    GtkWidget *card_view;
};

G_DEFINE_FINAL_TYPE(LActionSelector, l_action_selector, GTK_TYPE_BOX)


static void
selected_callback(GtkDropDown *self, GParamSpec *spec, gpointer data) {
    LActionSelector *selector = L_ACTION_SELECTOR(data);
    guint item = gtk_drop_down_get_selected(self);
}

static void
fill_cards(LActionSelector *self) {
    GtkWidget *default_action = GTK_WIDGET(l_default_card_new());
    GtkWidget *none = gtk_label_new("Button actions are disabled");
    GtkWidget *keypress = GTK_WIDGET(l_keypress_card_new());
    GtkWidget *gestures = GTK_WIDGET(l_gesture_card_new());
    GtkWidget *cycle_dpi = gtk_label_new("CYCLE_DPI");
    GtkWidget *toggle_smsh = gtk_label_new("TOGGLE_SMARTSHIFT");
    GtkWidget *toggle_hisc = gtk_label_new("TOGGLE_HIRESSCROLL");
    GtkWidget *change_dpi = gtk_label_new("CHANGE_DPI");
    GtkWidget *change_host = gtk_label_new("CHANGE_HOST");

    gtk_stack_add_named(GTK_STACK(self->card_view), default_action, action_names[DEFAULT]);
    gtk_stack_add_named(GTK_STACK(self->card_view), none, action_names[NONE]);
    gtk_stack_add_named(GTK_STACK(self->card_view), keypress, action_names[KEYPRESS]);
    gtk_stack_add_named(GTK_STACK(self->card_view), gestures, action_names[GESTURES]);
    gtk_stack_add_named(GTK_STACK(self->card_view), cycle_dpi, action_names[CYCLE_DPI]);
    gtk_stack_add_named(GTK_STACK(self->card_view), toggle_smsh, action_names[TOGGLE_SMARTSHIFT]);
    gtk_stack_add_named(GTK_STACK(self->card_view), toggle_hisc, action_names[TOGGLE_HIRESSCROLL]);
    gtk_stack_add_named(GTK_STACK(self->card_view), change_dpi, action_names[CHANGE_DPI]);
    gtk_stack_add_named(GTK_STACK(self->card_view), change_host, action_names[CHANGE_HOST]);
}

static void
set_data_in_card(GtkWidget *card, Action action) {
    if (L_IS_ACTION_CARD(card)) {
        l_action_card_set_action(L_ACTION_CARD(card), action);
    } else {
        g_print("== Card \"%s\" is not implemented Interface ==\n", action_names[action.type]);
    }
}

void
l_action_selector_set_selected(LActionSelector *self, Action action) {
    gtk_drop_down_set_selected(GTK_DROP_DOWN(self->selector), action.type);
    set_data_in_card(gtk_stack_get_child_by_name(GTK_STACK(self->card_view),
                                                 action_names[action.type]), action);
    gtk_stack_set_visible_child_name(GTK_STACK(self->card_view), action_names[action.type]);
}

LActionSelector *
l_action_selector_new(void) {
    LActionSelector *self = g_object_new(L_TYPE_ACTION_SELECTOR, NULL);
    return self;
}

GtkWidget *
l_action_selector_get_view(LActionSelector *self) {
    return self->card_view;
}

static void
l_action_selector_class_init(LActionSelectorClass *klass) {}

static void
l_action_selector_init(LActionSelector *self) {
    int margin = 20;
    self->selector = gtk_drop_down_new_from_strings((const char *const *) action_names);
    self->card_view = gtk_stack_new();
    fill_cards(self);

    g_object_set(self,
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 NULL);

    gtk_widget_set_margin_start(GTK_WIDGET(self), margin);
    gtk_widget_set_margin_end(GTK_WIDGET(self), margin);
    gtk_widget_set_margin_bottom(GTK_WIDGET(self), (int) (margin * 0.5));
    gtk_box_append(GTK_BOX(self), self->selector);

    g_signal_connect(self->selector, "notify::selected-item", G_CALLBACK(selected_callback), self);
}
