/* l-device-page.c
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

#include "l-device-page.h"

struct _LDevicePage {
    GtkBox parent_instance;

    DeviceDescription *device;
    LPrefPanel *device_pref_panel;
    LButtonPrefPanel *button_pref_panel;
    GtkWidget *device_name_button;
    GtkWidget *battery_state;
    GtkWidget *overlay;
    GSList *buttons;
};

G_DEFINE_FINAL_TYPE (LDevicePage, l_device_page, GTK_TYPE_BOX)


static void
page_panels_resize(LDevicePage *self) {
    int width = gtk_widget_get_width(GTK_WIDGET(self->overlay));
    int height = gtk_widget_get_height(GTK_WIDGET(self->overlay));

    if (gtk_widget_get_visible(GTK_WIDGET(self->device_pref_panel))) {
        if (width < height) {
            l_pref_panel_expand(self->device_pref_panel);
        } else {
            l_pref_panel_centered(self->device_pref_panel, width);
        }
    }

    if (gtk_widget_get_visible(GTK_WIDGET(self->button_pref_panel))) {
        if (width < height) {
            l_button_pref_panel_expand(self->button_pref_panel);
        } else {
            l_button_pref_panel_centered(self->button_pref_panel, width);
        }
    }
}

static void
clicked_name_button(GtkWidget *button, gpointer data) {
    LDevicePage *self = (LDevicePage *) data;

    g_object_set(self->device_pref_panel, "visible", TRUE, NULL);
    g_object_set(self->button_pref_panel, "visible", FALSE, NULL);

    page_panels_resize(self);
}

static void
clicked_device_button(GtkWidget *button, gpointer data) {
    LDevicePage *self = (LDevicePage *) data;

    g_object_set(self->device_pref_panel, "visible", FALSE, NULL);
    g_object_set(self->button_pref_panel, "visible", TRUE, NULL);

    page_panels_resize(self);
}

static void
fill_mx_master_buttons_list(LDevicePage *self) {
    GSList *buttons_description = self->device->buttons;

   /*
    LDeviceButton *scroll_wheel = l_device_button_new(
            0.62, 0.21,G_CALLBACK(clicked_device_button),self);
    LDeviceButton *horizontal_wheel = l_device_button_new(
            0.51, 0.45,G_CALLBACK(clicked_device_button),self);
    LDeviceButton *copy_button = l_device_button_new(
            0.39, 0.45,G_CALLBACK(clicked_device_button),self);
    LDeviceButton *paste_button = l_device_button_new(
            0.42, 0.545,G_CALLBACK(clicked_device_button),self);
    LDeviceButton *dpi_button = l_device_button_new(
            0.68, 0.37,G_CALLBACK(clicked_device_button),self);
    LDeviceButton *gestures_button = l_device_button_new(
            0.265, 0.58,G_CALLBACK(clicked_device_button),self);

    self->buttons = g_slist_append(self->buttons, scroll_wheel);
    self->buttons = g_slist_append(self->buttons, horizontal_wheel);
    self->buttons = g_slist_append(self->buttons, copy_button);
    self->buttons = g_slist_append(self->buttons, paste_button);
    self->buttons = g_slist_append(self->buttons, dpi_button);
    self->buttons = g_slist_append(self->buttons, gestures_button);
    */
    while (buttons_description != NULL) {
        ButtonDescription *description = buttons_description->data;

        self->buttons = g_slist_append(self->buttons,l_device_button_new(
                description->x_offset,
                description->y_offset,
                G_CALLBACK(clicked_device_button),
                self
                ));

        buttons_description = g_slist_next(buttons_description);
    }
}

static void
fill_buttons_container(GtkWidget *container, LDevicePage *self) {
    GSList *temp = self->buttons;

    while (temp != NULL) {
        gtk_box_append(GTK_BOX(container), GTK_WIDGET(temp->data));
        temp = g_slist_next(temp);
    }
}

static void
page_set_device_name(LDevicePage *self) {
    gtk_button_set_label(GTK_BUTTON(self->device_name_button), self->device->name->str);
    g_signal_connect(self->device_name_button, "clicked", G_CALLBACK(clicked_name_button), self);
}

static void
page_set_device_image(LDevicePage *self) {
    GtkWidget *device_image = gtk_image_new_from_resource(self->device->image_path->str);
    gtk_overlay_set_child(GTK_OVERLAY(self->overlay), device_image);
}

static void
page_set_battery_state(LDevicePage *self, const char *state) {
    gtk_image_set_from_resource(GTK_IMAGE(self->battery_state), state);
}

static void
page_set_buttons_layer(LDevicePage *self) {
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkLayoutManager *bin = gtk_bin_layout_new();

    gtk_widget_set_layout_manager(container, bin);

    g_object_set(container,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    fill_mx_master_buttons_list(self);
    fill_buttons_container(container, self);

    gtk_overlay_add_overlay(GTK_OVERLAY(self->overlay), container);
}

gboolean
page_resize(GtkOverlay *overlay, GtkWidget *widget, GdkRectangle *allocation, gpointer data) {
    int width = gtk_widget_get_width(GTK_WIDGET(overlay));
    int height = gtk_widget_get_height(GTK_WIDGET(overlay));
    int size = MIN(width, height);
    int half_button_size = (L_DEVICE_BUTTON_SIZE / 2);

    LDevicePage *page = (LDevicePage *) data;
    GSList *buttons = page->buttons;

    gtk_widget_set_size_request(widget, size, size);
    page_panels_resize(page);

    while (buttons != NULL) {
        LDeviceButton *button = buttons->data;
        offset_t *offset = l_device_button_get_offset(button);

        gtk_widget_set_margin_start(GTK_WIDGET(button),
                                    (int) (size * offset->x) - half_button_size);
        gtk_widget_set_margin_top(GTK_WIDGET(button),
                                  (int) (size * offset->y) - half_button_size);

        buttons = g_slist_next(buttons);
    }

    return TRUE;
}

static void
page_set_self(LDevicePage *self) {
    page_set_device_name(self);
    page_set_device_image(self);
    page_set_battery_state(self, L_BATTERY_20);
    page_set_buttons_layer(self);
    l_pref_panel_configure(self->device_pref_panel, self->device->conf);

    g_signal_connect(self->overlay, "get-child-position", G_CALLBACK(page_resize), self);
}

LDevicePage *
l_device_page_new(gpointer device) {
    LDevicePage *device_page = g_object_new(L_TYPE_DEVICE_PAGE, NULL);

    device_page->device = (DeviceDescription *) (device);
    page_set_self(device_page);

    return device_page;
}

static void
l_device_page_class_init(LDevicePageClass *klass) {}

static void
l_device_page_init(LDevicePage *self) {
    GtkLayoutManager *bin_layout = gtk_bin_layout_new();

    self->device = NULL;
    self->device_name_button = gtk_button_new();
    self->device_pref_panel = l_pref_panel_new();
    self->button_pref_panel = l_button_pref_panel_new();
    self->battery_state = gtk_image_new();
    self->overlay = gtk_overlay_new();
    self->buttons = NULL;

    gtk_widget_set_layout_manager(GTK_WIDGET(self), bin_layout);
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->overlay));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->device_name_button));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->battery_state));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->device_pref_panel));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->button_pref_panel));

    g_object_set(self,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);

    g_object_set(self->device_name_button,
                 "name", "DeviceName",
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    g_object_set(self->battery_state,
                 "valign", GTK_ALIGN_END,
                 "halign", GTK_ALIGN_START,
                 NULL);


    g_object_set(self->overlay,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);

    gtk_widget_set_margin_start(self->battery_state, 20);
    gtk_widget_set_margin_bottom(self->battery_state, 17);
    gtk_widget_set_size_request(self->battery_state, 50, 40);
}