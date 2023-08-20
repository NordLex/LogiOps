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
};

G_DEFINE_FINAL_TYPE (LPrefPanel, l_pref_panel, GTK_TYPE_BOX)

static void l_pref_panel_add_title(GtkWidget * parent, const char *text) {
    GtkWidget * title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), text);
    g_object_set(title, "halign", GTK_ALIGN_CENTER, NULL);
    gtk_box_append(GTK_BOX(parent), title);
}

static void l_pref_panel_apply_button_clicked(GtkWidget *button, gpointer data) {
    LPrefPanel *self = (LPrefPanel *) data;
    g_object_set(G_OBJECT(self), "visible", FALSE, NULL);
}

static void l_pref_panel_add_apply_button(GtkWidget * parent) {
    GtkWidget * button_title = gtk_label_new("Apply");
    GtkWidget * button = gtk_button_new();
    gpointer data = (gpointer *) parent;

    gtk_button_set_child(GTK_BUTTON(button), button_title);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(l_pref_panel_apply_button_clicked), data);

    gtk_box_append(GTK_BOX(parent), button);
}

static void l_pref_panel_add_dpi_slider(GtkWidget * parent) {
    double dpi_value = 1200;
    GtkAdjustment *adjustment = gtk_adjustment_new(dpi_value, 400, 2700, 100.0, 0.5, 0.5);
    GtkWidget *dpi_slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment);

    gtk_box_append(GTK_BOX(parent), dpi_slider);
}


LPrefPanel * l_pref_panel_new(void) {
    LPrefPanel * pref_panel = g_object_new(L_TYPE_PREF_PANEL, NULL);
    GtkWidget * pref_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    g_object_set(pref_container,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);
    l_pref_panel_add_dpi_slider(pref_container);

    l_pref_panel_add_title(GTK_WIDGET(pref_panel), "Gesture Button");
    gtk_box_append(GTK_BOX(pref_panel), pref_container);
    l_pref_panel_add_apply_button(GTK_WIDGET(pref_panel));

    return pref_panel;
}

static void l_pref_panel_class_init(LPrefPanelClass * klass) {}

static void l_pref_panel_init(LPrefPanel * self) {;
    g_object_set(self,
                 "name", "PrefPanel",
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 "halign", GTK_ALIGN_END,
                 "visible", FALSE,
                 NULL);

    gtk_widget_set_size_request(GTK_WIDGET(self), 450, -1);
}