//
// Created by nordlex on 28.07.2023.
//

#include "l-device-button.h"

const char * DEVICE_BUTTON_STYLE [3] =  {"white_frame", "circular", "flat"};

struct _LDeviceButton {
    GtkButton parent_instance;
    offset_t offset;
};

G_DEFINE_FINAL_TYPE (LDeviceButton, l_device_button, GTK_TYPE_BUTTON)

offset_t * l_device_button_get_offset(LDeviceButton * self) {
    return &self->offset;
}

LDeviceButton * l_device_button_new(gdouble x_offset, gdouble y_offset, GCallback callback) {
    LDeviceButton * object = g_object_new(L_TYPE_DEVICE_BUTTON, NULL);

    object->offset.x = x_offset;
    object->offset.y = y_offset;

    g_signal_connect(G_OBJECT(object), "clicked", callback, object);

    return object;
}

static void l_device_button_class_init(LDeviceButtonClass * klass) {}

static void l_device_button_init(LDeviceButton * self) {
    gtk_widget_set_css_classes(GTK_WIDGET(self), DEVICE_BUTTON_STYLE);
    gtk_widget_set_size_request(GTK_WIDGET(self),
                                L_DEVICE_BUTTON_SIZE,
                                L_DEVICE_BUTTON_SIZE);

    g_object_set(self,
                 "valign", GTK_ALIGN_START,
                 "halign", GTK_ALIGN_START,
                 NULL);
}