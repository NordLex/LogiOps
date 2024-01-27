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


struct _LKeypressCard {
    GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (LKeypressCard, l_keypress_card, GTK_TYPE_BOX)


GtkWidget *
make_key_card(GString *text) {
    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new(text->str);

    g_object_set(card,
                 "name", "KeyCard",
                 NULL);

    gtk_box_append(GTK_BOX(card), label);

    return card;
}

void
keypress_card_clear(LKeypressCard *self) {
    GtkWidget *child = NULL;

    do {
        child = gtk_widget_get_last_child(GTK_WIDGET(self));
        if (child != NULL)
            gtk_box_remove(GTK_BOX(self), child);
    } while (child != NULL);
}

void
l_keypress_card_set_data(LKeypressCard *self, GSList *keys) {
    GSList *temp_keys = keys;

    keypress_card_clear(self);

    while (temp_keys != NULL) {
        GString *key = temp_keys->data;
        GtkWidget *card = make_key_card(key);
        gtk_box_append(GTK_BOX(self), card);
        temp_keys = g_slist_next(temp_keys);
    }
}

LKeypressCard *
l_keypress_card_new(void) {
    return g_object_new(L_TYPE_KEYPRESS_CARD, NULL);
}

static void
l_keypress_card_class_init(LKeypressCardClass *klass) {}

static void
l_keypress_card_init(LKeypressCard *self) {
    g_object_set(self,
                 "name", "KeypressCard",
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
}