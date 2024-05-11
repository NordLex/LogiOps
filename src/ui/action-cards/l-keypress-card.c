/* l-keypress-card.c
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

#include "l-keypress-card.h"

static void
action_card_interface_init(LActionCardInterface *iface);


struct _LKeypressCard {
    GtkButton parent_instance;

    GtkWindow *key_grab_window;
};

G_DEFINE_TYPE_WITH_CODE(LKeypressCard, l_keypress_card, GTK_TYPE_BUTTON,
                        G_IMPLEMENT_INTERFACE(L_TYPE_ACTION_CARD, action_card_interface_init))


static void
keypress_card_set_action(LActionCard *self, Action action) {
    Keypress *keypress = action.self;

    gtk_button_set_child(GTK_BUTTON(self),
                         GTK_WIDGET(l_keys_label_new(keypress->keys)));
}

static GtkWindow *
get_root_window(GtkWidget *child) {
    GtkRoot *root = gtk_widget_get_root(child);
    GtkWindow *window = GTK_WINDOW(root);

    if (L_IS_WINDOW(window))
        return window;
    else
        return NULL;
}

static void
save_keys_callback(LKeyGrabWindow *window, gpointer data) {
    GSList *keys_list = l_key_grab_window_get_keys(window);

    gtk_button_set_child(GTK_BUTTON(data),
                         GTK_WIDGET(l_keys_label_new(keys_list)));
}

static void
self_clicked_callback(GtkWidget *self, gpointer data) {
    LKeypressCard *self_card = L_KEYPRESS_CARD(self);
    GtkWindow *root_window = get_root_window(GTK_WIDGET(self));

    self_card->key_grab_window = GTK_WINDOW(l_key_grab_window_new());
    l_key_grab_window_set_parent(L_KEY_GRAB_WINDOW(self_card->key_grab_window), root_window);

    g_signal_connect(self_card->key_grab_window, "save-keys", G_CALLBACK(save_keys_callback), self);

    gtk_window_present(GTK_WINDOW(self_card->key_grab_window));
}

LKeypressCard *
l_keypress_card_new(void) {
    return g_object_new(L_TYPE_KEYPRESS_CARD, NULL);
}

static void
action_card_interface_init(LActionCardInterface *iface) {
    iface->set_action = keypress_card_set_action;
}

static void
l_keypress_card_class_init(LKeypressCardClass *klass) {}

static void
l_keypress_card_init(LKeypressCard *self) {
    g_object_set(self,
                 "name", "KeypressCard",
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    g_signal_connect(self, "clicked", G_CALLBACK(self_clicked_callback), NULL);

    gtk_button_set_has_frame(GTK_BUTTON(self), FALSE);
}