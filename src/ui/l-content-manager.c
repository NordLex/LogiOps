/* l-content-manager.h
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

#include "l-content-manager.h"


struct _LContentManager {
    GObject parent_instance;
    GtkWidget * overlay;
    GSList * buttons;
};

G_DEFINE_FINAL_TYPE (LContentManager, l_content_manager, G_TYPE_OBJECT)

/*  Bung  */
static void clicked_button(GtkWidget * button, gpointer data) {}

static void set_frame(GtkWidget * widget) {
    const char * overlay_style[] = {"frame"};
    gtk_widget_set_css_classes(widget, overlay_style);
}

/*  Sets the device image   */
static void l_content_manager_set_image(LContentManager * self) {
    GtkWidget * device_image = gtk_image_new_from_resource(L_DEVICE_IMAGE);
    gtk_overlay_set_child(GTK_OVERLAY(self->overlay), device_image);
}

/**/
static void fill_buttons_container(GtkWidget * container, LContentManager * self) {
    GSList * temp = self->buttons;

    g_object_set(container,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    while (temp != NULL) {
        gtk_box_append(GTK_BOX(container), GTK_WIDGET(temp->data));
        temp = g_slist_next(temp);
    }
}

/**/
static void fill_buttons_list(LContentManager * self) {
    LDeviceButton * scroll_wheel = l_device_button_new(0.62, 0.21, G_CALLBACK(clicked_button));
    LDeviceButton * horizontal_wheel = l_device_button_new(0.51, 0.45, G_CALLBACK(clicked_button));
    LDeviceButton * copy_button = l_device_button_new(0.39, 0.45, G_CALLBACK(clicked_button));
    LDeviceButton * paste_button = l_device_button_new(0.42, 0.545, G_CALLBACK(clicked_button));
    LDeviceButton * dpi_button = l_device_button_new(0.68, 0.37, G_CALLBACK(clicked_button));
    LDeviceButton * gestures_button = l_device_button_new(0.265, 0.58, G_CALLBACK(clicked_button));

    self->buttons = g_slist_append(self->buttons, scroll_wheel);
    self->buttons = g_slist_append(self->buttons, horizontal_wheel);
    self->buttons = g_slist_append(self->buttons, copy_button);
    self->buttons = g_slist_append(self->buttons, paste_button);
    self->buttons = g_slist_append(self->buttons, dpi_button);
    self->buttons = g_slist_append(self->buttons, gestures_button);
}

/**/
static void l_content_manager_set_buttons_layer(LContentManager * self) {
    GtkWidget * buttons_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkLayoutManager * binLayout = gtk_bin_layout_new();
    gtk_widget_set_layout_manager(buttons_container, binLayout);

    g_object_set(buttons_container,"valign", GTK_ALIGN_CENTER, "halign", GTK_ALIGN_CENTER, NULL);

    fill_buttons_list(self);
    fill_buttons_container(buttons_container, self);

    gtk_overlay_add_overlay(GTK_OVERLAY(self->overlay), GTK_WIDGET(buttons_container));
}

/*
 *  Change the value buttons offset,
 *  when resizing the window
 *
 */
gboolean l_content_manager_resize(GtkOverlay * overlay, GtkWidget * widget,
                                  GdkRectangle * allocation, gpointer data) {
    int width = gtk_widget_get_width(GTK_WIDGET(overlay));
    int height = gtk_widget_get_height(GTK_WIDGET(overlay));
    int size = MIN(width, height);

    LContentManager * manager = (LContentManager *) data;
    GSList * buttons = manager->buttons;

    gtk_widget_set_size_request(widget, size, size);

    while (buttons != NULL) {
        int half_button_size = (L_DEVICE_BUTTON_SIZE / 2);
        LDeviceButton * button = buttons->data;
        offset_t * offset = l_device_button_get_offset(button);

        gtk_widget_set_margin_start(GTK_WIDGET(button),
                                    (int) (size * offset->x) - half_button_size);
        gtk_widget_set_margin_top(GTK_WIDGET(button),
                                  (int) (size * offset->y) - half_button_size);

        buttons = g_slist_next(buttons);
    }

    return TRUE;
}

/* */
void l_content_manager_set_content(LContentManager * self) {
    l_content_manager_set_image(self);
    l_content_manager_set_buttons_layer(self);

    g_signal_connect(self->overlay, "get-child-position", G_CALLBACK(l_content_manager_resize), self);
}

/* */
GtkWidget * l_content_manager_get_content(LContentManager * self) {
    l_content_manager_set_content(self);
    return self->overlay;
}

LContentManager * l_content_manager_new(void) {
    return g_object_new(L_TYPE_CONTENT_MANAGER, NULL);
}

static void l_content_manager_class_init(LContentManagerClass * Klass) {}

static void l_content_manager_init(LContentManager * self) {
    self->overlay = gtk_overlay_new();
    g_object_set(self->overlay,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);
    self->buttons = NULL;
}