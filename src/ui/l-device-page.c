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

    DeviceDescription *device_description;
    LPrefPanel *device_pref_panel;
    LButtonPrefPanel *button_pref_panel;
    GtkWidget *device_name_button;
    GtkWidget *battery_state;
    GtkWidget *overlay;
    GtkGesture *background_controller;
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
    LDevicePage *self = L_DEVICE_PAGE(data);

    g_object_set(self->device_pref_panel, "visible", TRUE, NULL);
    g_object_set(self->button_pref_panel, "visible", FALSE, NULL);

    page_panels_resize(self);
}

static void
clicked_background(GtkGesture *gesture, int n_press, double x, double y, gpointer data) {
    LDevicePage *self = L_DEVICE_PAGE(data);

    g_object_set(self->device_pref_panel, "visible", FALSE, NULL);
    g_object_set(self->button_pref_panel, "visible", FALSE, NULL);
}

static void
clicked_button_pref_panel_active(GtkWidget *button, gpointer device_page) {
    LDevicePage *self = (LDevicePage *) device_page;
    ButtonDescription *description = l_device_button_get_description(L_DEVICE_BUTTON(button));

    l_button_pref_panel_configure(self->button_pref_panel, description);

    g_object_set(self->device_pref_panel, "visible", FALSE, NULL);
    g_object_set(self->button_pref_panel, "visible", TRUE, NULL);

    page_panels_resize(self);
}

static void
clicked_battery_state(GtkWidget *button, gpointer data) {
    GtkWidget *battery_image = gtk_button_get_child(GTK_BUTTON(button));
    gtk_image_set_from_resource(GTK_IMAGE(battery_image), L_BATTERY_50);
}

static void
fill_buttons_list(LDevicePage *self) {
    GSList *buttons_description = self->device_description->buttons;

    while (buttons_description != NULL) {
        ButtonDescription *description = buttons_description->data;
        LDeviceButton *device_button = l_device_button_new(description, self);

        g_signal_connect(device_button, "clicked",
                         G_CALLBACK(clicked_button_pref_panel_active), self);

        self->buttons = g_slist_append(self->buttons, device_button);

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
    gtk_button_set_label(GTK_BUTTON(self->device_name_button),
                         self->device_description->name->str);
    g_signal_connect(self->device_name_button, "clicked", G_CALLBACK(clicked_name_button), self);
}

static void
page_set_device_image(LDevicePage *self) {
    GtkWidget *device_image = gtk_image_new_from_resource(
            self->device_description->image_path->str);
    gtk_overlay_set_child(GTK_OVERLAY(self->overlay), device_image);
}

static void
page_set_battery_state(LDevicePage *self, const char *state) {
    GtkWidget *battery_image = gtk_button_get_child(GTK_BUTTON(self->battery_state));
    gtk_image_set_from_resource(GTK_IMAGE(battery_image), state);
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

    fill_buttons_list(self);
    fill_buttons_container(container, self);

    gtk_overlay_add_overlay(GTK_OVERLAY(self->overlay), container);
}

static gboolean
page_resize(GtkOverlay *overlay, GtkWidget *widget, GdkRectangle *allocation, gpointer data) {
    LDevicePage *page;
    GSList *buttons;

    int width = gtk_widget_get_width(GTK_WIDGET(overlay));
    int height = gtk_widget_get_height(GTK_WIDGET(overlay));
    int size = MIN(width, height);
    int half_button_size = (L_DEVICE_BUTTON_SIZE / 2);

    if (NULL == data) return FALSE;

    page = L_DEVICE_PAGE(data);
    buttons = page->buttons;

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
    l_pref_panel_configure(self->device_pref_panel, self->device_description->conf);

    g_signal_connect(self->overlay, "get-child-position", G_CALLBACK(page_resize), self);
}

GtkWidget *
l_device_page_new(gpointer device_description, GtkWindow *key_grab_window) {
    LDevicePage *self = g_object_new(L_TYPE_DEVICE_PAGE, NULL);

    self->device_description = (DeviceDescription *) (device_description);
    self->button_pref_panel = l_button_pref_panel_new(key_grab_window);
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->button_pref_panel));
    page_set_self(self);

    return GTK_WIDGET(self);
}

static void
l_device_page_class_init(LDevicePageClass *klass) {}

static void
l_device_page_init(LDevicePage *self) {
    GtkLayoutManager *bin_layout = gtk_bin_layout_new();

    self->device_description = NULL;
    self->device_name_button = gtk_button_new();
    self->device_pref_panel = l_pref_panel_new();
    self->battery_state = gtk_button_new();
    self->overlay = gtk_overlay_new();
    self->background_controller = gtk_gesture_click_new();
    self->buttons = NULL;

    gtk_widget_set_layout_manager(GTK_WIDGET(self), bin_layout);
    gtk_widget_add_controller(GTK_WIDGET(self->overlay),
                              GTK_EVENT_CONTROLLER(self->background_controller));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->overlay));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->device_name_button));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->battery_state));
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->device_pref_panel));

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

    g_signal_connect(self->background_controller, "released", G_CALLBACK(clicked_background), self);
    g_signal_connect(self->battery_state, "clicked", G_CALLBACK(clicked_battery_state), NULL);

    gtk_button_set_child(GTK_BUTTON(self->battery_state), gtk_image_new());
    gtk_widget_add_css_class(self->battery_state, "flat");
    gtk_widget_set_margin_start(self->battery_state, 20);
    gtk_widget_set_margin_bottom(self->battery_state, 17);
    gtk_widget_set_size_request(self->battery_state, 50, 40);
}