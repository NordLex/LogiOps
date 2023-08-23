/* l-button-pref-panel.c
 *
 * Copyright 2023 NordLex
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

#include "l-pref-panel.h"


struct _LPrefPanel {
    GtkBox parent_instance;

    GtkWidget * title;
    GtkWidget * text_box;
    GtkWidget * pref_container;
    GtkWidget * apply_button;
};

G_DEFINE_FINAL_TYPE (LPrefPanel, l_pref_panel, GTK_TYPE_BOX)

static void l_pref_panel_apply_button_clicked(GtkWidget *button, gpointer data) {
    LPrefPanel *self = (LPrefPanel *) data;
    g_object_set(G_OBJECT(self), "visible", FALSE, NULL);
}

static void l_pref_panel_init_apply_button(LPrefPanel * self) {
    GtkWidget * button_title = gtk_label_new("Apply");
    GCallback on_click = G_CALLBACK(l_pref_panel_apply_button_clicked);

    gtk_button_set_child(GTK_BUTTON(self->apply_button), button_title);
    g_signal_connect(G_OBJECT(self->apply_button), "clicked", on_click, self);
}

static void l_pref_panel_init_content(LPrefPanel * self, const char *label ) {
    gtk_label_set_markup(GTK_LABEL(self->title), label);

}

void l_pref_panel_configure(LPrefPanel * self, gpointer button_conf) {
    l_pref_panel_init_content(self, "Configure button");
    l_pref_panel_init_apply_button(self);
}

LPrefPanel * l_pref_panel_new(void) {
    LPrefPanel * pref_panel = g_object_new(L_TYPE_PREF_PANEL, NULL);
    return pref_panel;
}

static void l_pref_panel_class_init(LPrefPanelClass * klass) {}

static void l_pref_panel_init(LPrefPanel * self) {
    self->title = gtk_label_new(NULL);
    self->text_box = gtk_text_view_new();
    self->pref_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    self->apply_button = gtk_button_new();

    gtk_box_append(GTK_BOX(self), self->title);
    gtk_box_append(GTK_BOX(self), self->pref_container);
    gtk_box_append(GTK_BOX(self->pref_container), self->text_box);
    gtk_box_append(GTK_BOX(self), self->apply_button);

    g_object_set(self,
                 "name", "PrefPanel",
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 "halign", GTK_ALIGN_END,
                 "visible", FALSE,
                 NULL);
    g_object_set(self->title,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
    g_object_set(self->text_box,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);
    g_object_set(self->pref_container,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);

    gtk_widget_set_margin_start(self->apply_button, 60);
    gtk_widget_set_margin_end(self->apply_button, 60);
    gtk_widget_set_size_request(GTK_WIDGET(self), 450, -1);

}