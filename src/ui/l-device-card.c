/* l-device-card.c
 *
 * Copyright 17.11.2023 NordLex
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

#include "l-device-card.h"

static guint card_signal;

struct _LDeviceCard {
    GtkBox parent_instance;

    DeviceDescription *description;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *image;
};

G_DEFINE_FINAL_TYPE(LDeviceCard, l_device_card, GTK_TYPE_BOX)

static void
card_signal_emit(GtkWidget *widget, gpointer data) {
    LDeviceCard *card = L_DEVICE_CARD(data);
    g_signal_emit(card, card_signal, 0);
}

static void
build_card(LDeviceCard *card) {
    gtk_label_set_label(GTK_LABEL(card->label),
                        card->description->name->str);
    gtk_image_set_from_resource(GTK_IMAGE(card->image),
                                card->description->image_path->str);
}

LDeviceCard *
l_device_card_new(DeviceDescription *description) {
    LDeviceCard *card = g_object_new(L_TYPE_DEVICE_CARD, NULL);

    card->description = description;
    build_card(card);

    return card;
}

DeviceDescription *
l_device_card_get_description(LDeviceCard *self) {
    return self->description;
}

static void
l_device_card_class_init(LDeviceCardClass *klass) {
    card_signal = g_signal_new("selected",
                             G_TYPE_FROM_CLASS(klass),
                             G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                             0,
                             NULL,
                             NULL,
                             NULL,
                             G_TYPE_NONE,
                             0,
                             NULL);
}

static void
l_device_card_init(LDeviceCard *self) {
    self->button = gtk_button_new();
    self->label = gtk_label_new(NULL);
    self->image = gtk_image_new();

    gtk_button_set_child(GTK_BUTTON(self->button), self->image);
    gtk_box_append(GTK_BOX(self), self->label);
    gtk_box_append(GTK_BOX(self), self->button);

    g_object_set(self,
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 "hexpand", TRUE,
                 "vexpand", TRUE,
                 NULL);

    g_object_set(self->button,
                 "name", "DeviceCard",
                 "hexpand", TRUE,
                 "vexpand", TRUE,
                 NULL);

    g_object_set(self->image,
                 "hexpand", TRUE,
                 "vexpand", TRUE,
                 NULL);

    g_signal_connect(self->button, "clicked", G_CALLBACK(card_signal_emit), self);

    gtk_widget_set_margin_top(self->label, 5);
}
