//
// Created by nordlex on 29.07.2023.
//

#include "mx-master-3.h"


static void set_device_image_to(GtkOverlay * content_view) {
    GtkWidget * device_picture = gtk_image_new_from_resource(L_DEVICE_IMAGE);

    gtk_overlay_set_child(GTK_OVERLAY(content_view), device_picture);
}

void logiops_set_mx_master_3_layer(GtkWidget * parent) {
    set_device_image_to(GTK_OVERLAY(parent));
    set_buttons_layer(GTK_OVERLAY(parent));
}
