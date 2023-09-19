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

#include "l-button-pref-panel.h"

struct _LButtonPrefPanel {
    GtkBox parent_instance;

    GtkWidget *title;
    GtkWidget *pref_container;
    GtkWidget *close_button;
};

G_DEFINE_FINAL_TYPE (LButtonPrefPanel, l_button_pref_panel, GTK_TYPE_BOX)

#define PANEL_WIDTH 450

static void
callback_close_button(GtkWidget *button, gpointer data) {
    LButtonPrefPanel *self = L_BUTTON_PREF_PANEL(data);
    g_object_set(G_OBJECT(self), "visible", FALSE, NULL);
}

static void
init_close_button(LButtonPrefPanel *self) {
    GtkWidget *title = gtk_label_new("Close");
    GCallback on_click = G_CALLBACK(callback_close_button);

    gtk_button_set_child(GTK_BUTTON(self->close_button), title);
    g_signal_connect(self->close_button, "clicked", on_click, self);
}

static void
init_title(LButtonPrefPanel *self, GString *name) {
    const char *format = "<span weight=\"bold\">\%s</span>";
    char *markup = g_markup_printf_escaped(format, name->str);

    gtk_label_set_markup(GTK_LABEL(self->title), markup);
    g_free(markup);
}

static void
init_content(LButtonPrefPanel *self, ButtonDescription *button_description) {
    init_title(self, button_description->name);
}

void
l_button_pref_panel_centered(LButtonPrefPanel *self, int width) {
    int panel_width = (int) (width * 0.4);

    if (panel_width < PANEL_WIDTH) {
        gtk_widget_set_size_request(GTK_WIDGET(self), PANEL_WIDTH, -1);
    } else {
        gtk_widget_set_size_request(GTK_WIDGET(self), panel_width, -1);
    }

    g_object_set(self,
                 "halign", GTK_ALIGN_END,
                 NULL);
}

void
l_button_pref_panel_expand(LButtonPrefPanel *self) {
    g_object_set(self,
                 "halign", FALSE,
                 NULL);
}

void
l_button_pref_panel_configure(LButtonPrefPanel *self, gpointer button_conf) {
    ButtonDescription *button_description = (ButtonDescription *) button_conf;
    init_content(self, button_description);
}

LButtonPrefPanel *
l_button_pref_panel_new(void) {
    return g_object_new(L_TYPE_BUTTON_PREF_PANEL, NULL);
}

static void
l_button_pref_panel_class_init(LButtonPrefPanelClass *klass) {}

static void
l_button_pref_panel_init(LButtonPrefPanel *self) {
    self->title = gtk_label_new(NULL);
    self->pref_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->close_button = gtk_button_new();

    gtk_box_append(GTK_BOX(self), self->title);
    gtk_box_append(GTK_BOX(self), self->pref_container);
    gtk_box_append(GTK_BOX(self), self->close_button);

    g_object_set(self,
                 "name", "ButtonPrefPanel",
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 10,
                 "halign", GTK_ALIGN_END,
                 "visible", FALSE,
                 NULL);
    g_object_set(self->title,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
    g_object_set(self->pref_container,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);

    init_close_button(self);
    gtk_widget_set_margin_start(self->close_button, 60);
    gtk_widget_set_margin_end(self->close_button, 60);
    gtk_widget_set_margin_start(self->pref_container, 5);
    gtk_widget_set_margin_end(self->pref_container, 5);
    gtk_widget_set_size_request(GTK_WIDGET(self), PANEL_WIDTH, -1);
}