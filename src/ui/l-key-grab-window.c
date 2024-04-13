/* l-key-grab-window.c
 *
 * Copyright 02.04.24 NordLex
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

#include "l-key-grab-window.h"


struct _LKeyGrabWindow {
    AdwWindow parent_instance;

    GtkWidget *window_container;
    GtkWidget *header_bar;
    GtkWidget *content;
};

G_DEFINE_FINAL_TYPE(LKeyGrabWindow, l_key_grab_window, ADW_TYPE_WINDOW)


static void
close_callback(GtkButton *button, gpointer data) {
    GtkWindow *window = GTK_WINDOW(data);

    gtk_window_close(window);
}

static GtkWidget *
make_header_bar(GtkWindow *window) {
    GtkWidget *bar = gtk_center_box_new();
    GtkWidget *close_button = gtk_button_new_from_icon_name("window-close-symbolic");

    gtk_center_box_set_end_widget(GTK_CENTER_BOX(bar), close_button);

    g_object_set(bar, "hexpand", TRUE, NULL);

    g_signal_connect(close_button, "clicked", G_CALLBACK(close_callback), window);

    return bar;
}

void
l_key_grab_window_set_parent(LKeyGrabWindow *self, GtkWindow *parent) {
    gtk_window_set_transient_for(GTK_WINDOW(self), parent);
}

LKeyGrabWindow *
l_key_grab_window_new(void) {
    LKeyGrabWindow *self = g_object_new(L_TYPE_KEY_GRAB_WINDOW, NULL);

    return self;
}

static void
l_key_grab_window_class_init(LKeyGrabWindowClass *klass) {}

static void
l_key_grab_window_init(LKeyGrabWindow *self) {
    GtkWidget *child = gtk_label_new("This KeyPress Grab Window");

    self->window_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    self->header_bar = make_header_bar(GTK_WINDOW(self));
    self->content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_window_set_modal(GTK_WINDOW(self), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(self), 400, 200);
    gtk_box_append(GTK_BOX(self->content), child);

    gtk_box_append(GTK_BOX(self->window_container), self->header_bar);
    gtk_box_append(GTK_BOX(self->window_container), self->content);

    adw_window_set_content(ADW_WINDOW(self), self->window_container);
}
