//
// Created by nordlex on 28.07.2023.
//

#pragma once

#include "../l-application-resources.h"

typedef struct {
    gdouble x;
    gdouble y;
} offset_t;

G_BEGIN_DECLS

#define L_TYPE_DEVICE_BUTTON (l_device_button_get_type())

G_DECLARE_FINAL_TYPE (LDeviceButton, l_device_button, L, DEVICE_BUTTON, GtkButton)

LDeviceButton * l_device_button_new(gdouble x_offset, gdouble y_offset, GCallback callback);

offset_t * l_device_button_get_offset(LDeviceButton * self);

G_END_DECLS
