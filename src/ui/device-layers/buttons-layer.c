//
// Created by nordlex on 02.08.2023.
//

#include "buttons-layer.h"

const char * button_box_style[] = {"frame"};

void clicked_button(GtkWidget * button, gpointer data) {

}

static void fill_buttons_container(GtkWidget * container, GSList * buttons) {
    GSList * temp = buttons;

    g_object_set(container,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    while (temp != NULL) {
        gtk_box_append(GTK_BOX(container), GTK_WIDGET(temp->data));
        temp = g_slist_next(temp);
    }
}

static void fill_buttons_list(GSList * list) {
    LDeviceButton * scroll_wheel = l_device_button_new(0.62, 0.21, G_CALLBACK(clicked_button));
    LDeviceButton * horizontal_wheel = l_device_button_new(0.51, 0.45, G_CALLBACK(clicked_button));
    LDeviceButton * copy_button = l_device_button_new(0.39, 0.45, G_CALLBACK(clicked_button));
    LDeviceButton * paste_button = l_device_button_new(0.42, 0.545, G_CALLBACK(clicked_button));
    LDeviceButton * dpi_button = l_device_button_new(0.68, 0.37, G_CALLBACK(clicked_button));
    LDeviceButton * gestures_button = l_device_button_new(0.265, 0.58, G_CALLBACK(clicked_button));

    list = g_slist_append(list, scroll_wheel);
    list = g_slist_append(list, horizontal_wheel);
    list = g_slist_append(list, copy_button);
    list = g_slist_append(list, paste_button);
    list = g_slist_append(list, dpi_button);
    list = g_slist_append(list, gestures_button);
}

gboolean resize_fun(GtkOverlay * overlay, GtkWidget * widget, GdkRectangle * allocation, gpointer data) {
    int overlay_width = gtk_widget_get_width(GTK_WIDGET(overlay));
    int overlay_height = gtk_widget_get_height(GTK_WIDGET(overlay));
    int size = MIN(overlay_width, overlay_height);

    GSList * buttons = (GSList *) data;
    gtk_widget_set_size_request(widget, size, size);

    while (buttons != NULL) {
        int half_size = (L_DEVICE_BUTTON_SIZE / 2);
        LDeviceButton * button = buttons->data;
        offset_t * offset = (offset_t *) l_device_button_get_offset(button);

        gtk_widget_set_margin_start(GTK_WIDGET(button), (int) (size * offset->x) - half_size);
        gtk_widget_set_margin_top(GTK_WIDGET(button), (int) (size * offset->y) - half_size);
        buttons = g_slist_next(buttons);
    }

    return TRUE;
}

void set_buttons_layer(GtkOverlay * parent) {
    GSList * buttons = NULL;
    GtkWidget * container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //GtkLayoutManager * binLayout = gtk_bin_layout_new();
    //gtk_widget_set_layout_manager(container, binLayout);

    gtk_widget_set_css_classes(GTK_WIDGET(container), button_box_style);
    gtk_widget_set_size_request(GTK_WIDGET(container), 300, 300);


    //fill_buttons_list(buttons);
    //fill_buttons_container(container, buttons);

    gtk_overlay_add_overlay(GTK_OVERLAY(parent), container);
    g_signal_connect(parent, "get-child-position", G_CALLBACK(resize_fun), buttons);
}