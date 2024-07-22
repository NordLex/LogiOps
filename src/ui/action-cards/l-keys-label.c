/* l-key-label.c
 *
 * Copyright 18.04.24 NordLex
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

#include "l-keys-label.h"


struct _LKeysLabel {
    GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE(LKeysLabel, l_keys_label, GTK_TYPE_BOX)


static const char *
keyval_name(guint key_code) {
    const char *key_name = gdk_keyval_name(key_code);

    if (key_code == 65507 || key_code == 65508)
        key_name = "Control";
    if (key_code == 65505 || key_code == 65506)
        key_name = "Shift";
    if (key_code == 65513 || key_code == 65027)
        key_name = "Alt";
    if (key_code == 0xffe7 || key_code == 0xffe8)
        key_name = "Meta";

    return key_name;
}

static GtkWidget *
key_label(const char *key_name) {
    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new(key_name);

    g_object_set(card,
                 "name", "KeyCard",
                 NULL);

    gtk_box_append(GTK_BOX(card), label);

    return card;
}

static GtkWidget *
key_label_delimiter(void) {
    GtkWidget *delimiter = gtk_label_new(" + ");
    g_object_set(delimiter, "name", "KeyCardDelimiter", NULL);
    return delimiter;
}

static void
set_labels(LKeysLabel *self, GSList *key_codes) {
    GSList *temp_keys = key_codes;

    while (NULL != temp_keys) {
        guint key_code = GPOINTER_TO_UINT(temp_keys->data);
        GtkWidget *card = key_label(keyval_name(key_code));

        gtk_box_append(GTK_BOX(self), card);

        if (NULL != temp_keys->next)
            gtk_box_append(GTK_BOX(self), key_label_delimiter());

        temp_keys = g_slist_next(temp_keys);
    }
}

LKeysLabel *
l_keys_label_new(GSList *key_codes) {
    LKeysLabel *self = g_object_new(L_TYPE_KEYS_LABEL, NULL);

    if (NULL != key_codes)
        set_labels(self, key_codes);

    return self;
}

static void
l_keys_label_class_init(LKeysLabelClass *klass) {}

static void
l_keys_label_init(LKeysLabel *self) {
    g_object_set(self,
                 "orientation", GTK_ORIENTATION_HORIZONTAL,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
}
