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

static guint save_signal;

struct _LKeyGrabWindow {
    AdwWindow parent_instance;

    GtkWidget *window_container;
    GtkWidget *header_bar;
    GtkWidget *content;
    GtkEventController *controller;
    GSList *keys;
};

G_DEFINE_FINAL_TYPE(LKeyGrabWindow, l_key_grab_window, ADW_TYPE_WINDOW)


#define CANCEL      "Cancel"
#define SAVE        "Save"
#define EXPLANATION "Press the button combination, you want to install"

static void
cancel_callback(GtkButton *button, gpointer data) {
    gtk_window_close(GTK_WINDOW(data));
}

static void
save_callback(GtkButton *button, gpointer data) {
    LKeyGrabWindow *self = L_KEY_GRAB_WINDOW(data);

    g_signal_emit(self, save_signal, 0);
    gtk_window_close(GTK_WINDOW(data));
}

static guint
get_keyval_en(guint keycode) {
    int entries = 1;
    GdkDisplay *display = gdk_display_get_default();
    guint *key_values[entries];

    gdk_display_map_keycode(display, keycode, NULL, key_values, &entries);

    return *key_values[0];
}

static gint
compare_keys(gconstpointer item_one, gconstpointer item_two) {
    return (gint) (GPOINTER_TO_UINT(item_one) - GPOINTER_TO_UINT(item_two));
}

static gboolean
key_released_callback(GtkEventControllerKey *event_controller,
                      guint keyval,
                      guint keycode,
                      GdkModifierType state,
                      gpointer data) {
    const char *child_name = "key-labels";
    LKeyGrabWindow *self = L_KEY_GRAB_WINDOW(data);
    GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(self->content), child_name);
    guint key_value = get_keyval_en(keycode);

    self->keys = g_slist_append(self->keys,
                                GUINT_TO_POINTER(gdk_keyval_to_upper(key_value)));
    self->keys = g_slist_reverse(g_slist_sort(self->keys,
                                              (GCompareFunc)compare_keys));

    if (NULL != child)
        gtk_stack_remove(GTK_STACK(self->content), child);

    gtk_stack_add_named(GTK_STACK(self->content),
                        GTK_WIDGET(l_keys_label_new(self->keys)),
                        child_name);
    gtk_stack_set_visible_child_name(GTK_STACK(self->content), child_name);

    return TRUE;
}

static GtkWidget *
make_header_bar(GtkWindow *window) {
    int margin = 8;
    int button_width = 90;
    int button_height = -1;
    GtkWidget *bar = gtk_center_box_new();
    GtkWidget *cancel_button = gtk_button_new_with_label(CANCEL);
    GtkWidget *save_button = gtk_button_new_with_label(SAVE);

    gtk_center_box_set_start_widget(GTK_CENTER_BOX(bar), save_button);
    gtk_center_box_set_end_widget(GTK_CENTER_BOX(bar), cancel_button);

    gtk_widget_set_margin_top(GTK_WIDGET(bar), margin);
    gtk_widget_set_margin_start(GTK_WIDGET(bar), margin);
    gtk_widget_set_margin_end(GTK_WIDGET(bar), margin);

    gtk_widget_add_css_class(cancel_button, "suggested-action");
    gtk_widget_set_size_request(save_button, button_width, button_height);
    gtk_widget_set_size_request(cancel_button, button_width, button_height);

    g_object_set(bar, "hexpand", TRUE, NULL);

    g_signal_connect(save_button, "clicked", G_CALLBACK(save_callback), window);
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(cancel_callback), window);

    return bar;
}

static GtkWidget *
preview_layer(void) {
    int margin = 20;
    GtkWidget *image = gtk_picture_new_for_resource(L_KEYBOARD_SVG);
    GtkWidget *content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkWidget *label = gtk_label_new(EXPLANATION);

    gtk_box_append(GTK_BOX(content), label);
    gtk_box_append(GTK_BOX(content), image);

    gtk_widget_set_margin_top   (content, margin);
    gtk_widget_set_margin_bottom(content, margin);
    gtk_widget_set_margin_start (content, margin);
    gtk_widget_set_margin_end   (content, margin);

    g_object_set(content, "vexpand", TRUE, "hexpand", TRUE, NULL);
    g_object_set(image,   "vexpand", TRUE, "hexpand", TRUE, NULL);

    return content;
}

static GtkWidget *
make_content(void) {
    GtkWidget *stack = gtk_stack_new();

    gtk_stack_add_named(GTK_STACK(stack), preview_layer(), "preview-layer");

    return stack;
}

GSList*
l_key_grab_window_get_keys(LKeyGrabWindow *self) {
    return self->keys;
}

void
l_key_grab_window_set_parent(LKeyGrabWindow *self, GtkWindow *parent) {
    gtk_window_set_transient_for(GTK_WINDOW(self), parent);
}

LKeyGrabWindow *
l_key_grab_window_new(void) {
    return g_object_new(L_TYPE_KEY_GRAB_WINDOW, NULL);
}

static void
l_key_grab_window_class_init(LKeyGrabWindowClass *klass) {
    save_signal = g_signal_new("save-keys",
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
l_key_grab_window_init(LKeyGrabWindow *self) {
    self->window_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    self->header_bar = make_header_bar(GTK_WINDOW(self));
    self->content = make_content();
    self->controller = gtk_event_controller_key_new();
    self->keys = NULL;

    gtk_window_set_modal(GTK_WINDOW(self), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(self), 450, 250);
    gtk_widget_add_controller(GTK_WIDGET(self), self->controller);

    gtk_box_append(GTK_BOX(self->window_container), self->header_bar);
    gtk_box_append(GTK_BOX(self->window_container), self->content);

    adw_window_set_content(ADW_WINDOW(self), self->window_container);

    g_signal_connect(self->controller, "key-released", G_CALLBACK(key_released_callback), self);
}
