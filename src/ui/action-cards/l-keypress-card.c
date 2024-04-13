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
    GtkWidget *container;
};

G_DEFINE_TYPE_WITH_CODE(LKeypressCard, l_keypress_card, GTK_TYPE_BUTTON,
                        G_IMPLEMENT_INTERFACE(L_TYPE_ACTION_CARD, action_card_interface_init))


static GtkWidget *
make_key_card(guint key_code) {
    const char *key_name = gdk_keyval_name(key_code);
    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new(key_name);

    g_object_set(card,
                 "name", "KeyCard",
                 NULL);

    gtk_box_append(GTK_BOX(card), label);

    return card;
}

static GtkWidget *
make_key_card_delimiter(void) {
    GtkWidget *delimiter = gtk_label_new(" + ");
    g_object_set(delimiter, "name", "KeyCardDelimiter", NULL);
    return delimiter;
}

static void
keypress_card_clear(GtkBox *container) {
    GtkWidget *child = NULL;

    do {
        child = gtk_widget_get_last_child(GTK_WIDGET(container));
        if (child != NULL)
            gtk_box_remove(container, child);
    } while (child != NULL);
}

static void
keypress_card_set_data(GtkBox *container, GSList *keys) {
    GSList *temp_keys = keys;

    keypress_card_clear(container);

    while (temp_keys != NULL) {
        guint key_code = GPOINTER_TO_UINT(temp_keys->data);
        GtkWidget *card = make_key_card(key_code);

        gtk_box_append(container, card);
        if (temp_keys->next != NULL)
            gtk_box_append(container, make_key_card_delimiter());
        temp_keys = g_slist_next(temp_keys);
    }
}

static void
keypress_card_set_action(LActionCard *self, Action action) {
    LKeypressCard *keypress_card = L_KEYPRESS_CARD(self);
    Keypress *keypress = action.self;
    keypress_card_set_data(GTK_BOX(keypress_card->container), keypress->keys);
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
self_clicked_callback(GtkWidget *self, gpointer data) {
    LKeypressCard *self_card = L_KEYPRESS_CARD(self);
    GtkWindow *root_window = get_root_window(GTK_WIDGET(self));

    self_card->key_grab_window = GTK_WINDOW(l_key_grab_window_new());
    l_key_grab_window_set_parent(L_KEY_GRAB_WINDOW(self_card->key_grab_window), root_window);
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
    self->container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    g_object_set(self,
                 "name", "KeypressCard",
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    g_object_set(self->container,
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    g_signal_connect(self, "clicked", G_CALLBACK(self_clicked_callback), NULL);

    gtk_button_set_has_frame(GTK_BUTTON(self), FALSE);
    gtk_button_set_child(GTK_BUTTON(self), self->container);
}