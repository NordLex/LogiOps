/* l-pref-panel.c
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

#include "l-pref-panel.h"


struct _LPrefPanel {
    GtkBox parent_instance;

    GtkWidget *main_box;
    GtkWidget *pref_container;
    GtkWidget *close_button;
    GtkWidget *save_button;
};

G_DEFINE_FINAL_TYPE (LPrefPanel, l_pref_panel, GTK_TYPE_BOX)

typedef struct {
    gboolean *state;
    GtkWidget *expander;
} ExpanderSwitch;


static void
callback_set_sm_state(GtkSwitch *widget, gboolean state, gpointer data) {
    ExpanderSwitch *exp_switch = (ExpanderSwitch *) data;

    adw_expander_row_set_enable_expansion(ADW_EXPANDER_ROW(exp_switch->expander), state);
}

static void
callback_set_dpi(GtkRange *widget, gpointer data) {
    LDevice *device = L_DEVICE(data);
    gint settings_value = (gint) gtk_range_get_value(widget);

    Dpi *dpi = l_device_get_dpi(device);
    gint tail = settings_value % dpi->step;
    gint rounded_value;
    if (tail > (dpi->step / 2))
        rounded_value = settings_value - tail + dpi->step;
    else
        rounded_value = settings_value - tail;

    l_device_set_dpi(device, rounded_value);
}

static void
callback_set_hires(GtkSwitch *widget, gboolean state, gpointer data) {
    LDevice *device = L_DEVICE(data);
    l_device_set_hiresscroll_hires(device, state);
    gtk_switch_set_active(widget, state);
}

static void
callback_set_invert(GtkSwitch *widget, gboolean state, gpointer data) {
    LDevice *device = L_DEVICE(data);
    l_device_set_hiresscroll_invert(device, state);
    gtk_switch_set_active(widget, state);
}

static void
callback_set_target(GtkSwitch *widget, gboolean state, gpointer data) {
    LDevice *device = L_DEVICE(data);
    l_device_set_hiresscroll_target(device, state);
    gtk_switch_set_active(widget, state);
}

static void
callback_close_button(GtkWidget *button, gpointer data) {
    LPrefPanel *self = L_PREF_PANEL(data);
    g_object_set(G_OBJECT(self), "visible", FALSE, NULL);
}

static void
callback_save_button(GtkWidget *button, gpointer data) {
    g_print("== Save ==\n");
}

static void
l_pref_panel_init_dpi(LDevice *device, GtkWidget *parent) {
    Dpi *dpi = l_device_get_dpi(device);
    GtkWidget *dpi_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *title = gtk_label_new(NULL);
    GtkWidget *scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                dpi->min, dpi->max, dpi->step);

    g_object_set(scale, "hexpand", TRUE, NULL);
    g_object_set(dpi_box, "name", "PrefGroup", NULL);

    gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
    gtk_range_set_value(GTK_RANGE(scale), (gdouble) dpi->dpi);
    gtk_box_append(GTK_BOX(dpi_box), title);
    gtk_label_set_markup(GTK_LABEL(title), "<span weight=\"bold\">DPI</span>");
    gtk_box_append(GTK_BOX(dpi_box), scale);
    gtk_box_append(GTK_BOX(parent), dpi_box);

    g_signal_connect(scale, "value-changed", G_CALLBACK(callback_set_dpi), device);
}

static void
l_pref_panel_init_smartshift(Smartshift *smartshift, GtkWidget *parent) {
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *main_label = gtk_label_new(NULL);
    ExpanderSwitch *exp_switch = g_malloc(sizeof(ExpanderSwitch));
    GtkWidget *state_switch = gtk_switch_new();

    GtkWidget *threshold_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *threshold_label = gtk_label_new("Threshold");
    GtkWidget *threshold_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                          0, 100, 1);
    GtkWidget *torque_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *torque_label = gtk_label_new("Torque");
    GtkWidget *torque_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                       0, 100, 1);

    g_object_set(threshold_box, "hexpand", TRUE, NULL);
    g_object_set(threshold_label, "hexpand", TRUE, "halign", GTK_ALIGN_START, NULL);
    g_object_set(threshold_scale, "halign", GTK_ALIGN_END, NULL);
    g_object_set(torque_box, "hexpand", TRUE, NULL);
    g_object_set(torque_label, "hexpand", TRUE, "halign", GTK_ALIGN_START, NULL);
    g_object_set(torque_scale, "halign", GTK_ALIGN_END, NULL);
    g_object_set(main_box,  "name", "PrefGroup", "hexpand", TRUE, NULL);

    gtk_box_append(GTK_BOX(threshold_box), threshold_label);
    gtk_box_append(GTK_BOX(threshold_box), threshold_scale);

    gtk_box_append(GTK_BOX(torque_box), torque_label);
    gtk_box_append(GTK_BOX(torque_box), torque_scale);

    gtk_box_append(GTK_BOX(main_box), main_label);
    gtk_label_set_markup(GTK_LABEL(main_label), "<span weight=\"bold\">Smartshift</span>");
    gtk_box_append(GTK_BOX(main_box), threshold_box);
    gtk_box_append(GTK_BOX(main_box), torque_box);

    exp_switch->state = &smartshift->on;
    g_object_set(state_switch, "valign", GTK_ALIGN_CENTER, NULL);

    gtk_switch_set_active(GTK_SWITCH(state_switch), *exp_switch->state);

    gtk_widget_set_size_request(threshold_scale, 300, -1);
    gtk_widget_set_size_request(torque_scale, 300, -1);

    gtk_range_set_value(GTK_RANGE(threshold_scale), smartshift->threshold);
    gtk_range_set_value(GTK_RANGE(torque_scale), smartshift->torque);

    g_signal_connect(state_switch, "state-set", G_CALLBACK(callback_set_sm_state), exp_switch);
    //g_signal_connect(threshold_scale, "value-changed", G_CALLBACK(callback_set_value), &smartshift->threshold);
    //g_signal_connect(torque_scale, "value-changed", G_CALLBACK(callback_set_value), &smartshift->torque);

    gtk_box_append(GTK_BOX(parent), main_box);
}

static void
l_pref_panel_init_hiresscroll(LDevice *device, GtkWidget *parent) {
    Hiresscroll *hiresscroll = l_device_get_hiresscroll(device);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *main_label = gtk_label_new(NULL);

    GtkWidget *switch_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *hires_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hires_switch = gtk_switch_new();

    GtkWidget *invert_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *invert_switch = gtk_switch_new();

    GtkWidget *target_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *target_switch = gtk_switch_new();


    g_object_set(hires_box, "halign", GTK_ALIGN_START, NULL);
    g_object_set(hires_switch,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
    g_object_set(invert_box, "hexpand", TRUE, "halign", GTK_ALIGN_CENTER, NULL);
    g_object_set(invert_switch,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
    g_object_set(target_box, "halign", GTK_ALIGN_END, NULL);
    g_object_set(target_switch,
                 "valign", GTK_ALIGN_CENTER,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);

    g_object_set(switch_box, "hexpand", TRUE, NULL);
    g_object_set(main_box,
                 "name", "PrefGroup",
                 "hexpand", TRUE,
                 NULL);

    gtk_switch_set_active(GTK_SWITCH(hires_switch), hiresscroll->hires);
    gtk_switch_set_active(GTK_SWITCH(invert_switch), hiresscroll->invert);
    gtk_switch_set_active(GTK_SWITCH(target_switch), hiresscroll->target);

    gtk_label_set_markup(GTK_LABEL(main_label), "<span weight=\"bold\">Hiresscroll</span>");
    gtk_widget_set_margin_start(hires_box, 10);
    gtk_widget_set_margin_end(target_box, 10);

    gtk_box_append(GTK_BOX(hires_box), gtk_label_new("Hires"));
    gtk_box_append(GTK_BOX(hires_box), hires_switch);
    gtk_box_append(GTK_BOX(invert_box), gtk_label_new("Invert"));
    gtk_box_append(GTK_BOX(invert_box), invert_switch);
    gtk_box_append(GTK_BOX(target_box), gtk_label_new("Target"));
    gtk_box_append(GTK_BOX(target_box), target_switch);

    gtk_box_append(GTK_BOX(switch_box), hires_box);
    gtk_box_append(GTK_BOX(switch_box), invert_box);
    gtk_box_append(GTK_BOX(switch_box), target_box);

    gtk_box_append(GTK_BOX(main_box), main_label);

    gtk_box_append(GTK_BOX(main_box), switch_box);

    g_signal_connect(hires_switch, "state-set", G_CALLBACK(callback_set_hires), device);
    g_signal_connect(invert_switch, "state-set", G_CALLBACK(callback_set_invert), device);
    g_signal_connect(target_switch, "state-set", G_CALLBACK(callback_set_target), device);

    gtk_box_append(GTK_BOX(parent), main_box);
}

static void
l_pref_panel_clear_content(GtkWidget *container) {
    GtkWidget *child = gtk_widget_get_first_child(container);
    while (child != NULL) {
        gtk_box_remove(GTK_BOX(container), child);
        child = gtk_widget_get_first_child(container);
    }
}

static void
l_pref_panel_init_content(LPrefPanel * self, gpointer device_conf) {
    LDevice *device = L_DEVICE(device_conf);
    Smartshift *smartshift = l_device_get_smartshift(device);
    Hiresscroll *hiresscroll = l_device_get_hiresscroll(device);

    g_signal_connect(G_OBJECT(self->save_button), "clicked", G_CALLBACK(callback_save_button), device);

    l_pref_panel_clear_content(self->pref_container);
    l_pref_panel_init_hiresscroll(device, self->pref_container);
    l_pref_panel_init_smartshift(smartshift, self->pref_container);
    l_pref_panel_init_dpi(device, self->pref_container);
}

void
l_pref_panel_centered(LPrefPanel *self, int width) {
    g_object_set(self,
                 "halign", GTK_ALIGN_CENTER,
                 "valign", GTK_ALIGN_START,
                 NULL);
    gtk_widget_set_size_request(GTK_WIDGET(self), (int) (width * 0.7), -1);
}

void
l_pref_panel_expand(LPrefPanel *self) {
    g_object_set(self,
                 "halign", FALSE,
                 "valign", FALSE,
                 NULL);
}

void
l_pref_panel_configure(LPrefPanel * self, gpointer device_conf) {
    l_pref_panel_init_content(self, device_conf);
}

LPrefPanel *
l_pref_panel_new(void) {
    return g_object_new(L_TYPE_PREF_PANEL, NULL);
}

static void
l_pref_panel_class_init(LPrefPanelClass * klass) {}

static void
l_pref_panel_init(LPrefPanel * self) {
    self->save_button = gtk_button_new_from_icon_name("object-select-symbolic");
    self->main_box = gtk_center_box_new();
    self->pref_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    self->close_button = gtk_button_new_from_icon_name("window-close-symbolic");

    gtk_center_box_set_start_widget(GTK_CENTER_BOX(self->main_box), self->save_button);
    gtk_center_box_set_center_widget(GTK_CENTER_BOX(self->main_box), self->pref_container);
    gtk_center_box_set_end_widget(GTK_CENTER_BOX(self->main_box), self->close_button);

    gtk_box_append(GTK_BOX(self), self->main_box);

    g_object_set(self,
                 "name", "PrefPanel",
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "halign", GTK_ALIGN_CENTER,
                 "valign", GTK_ALIGN_START,
                 "spacing", 10,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 "visible", FALSE,
                 NULL);

    g_object_set(self->pref_container,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);
    g_object_set(self->close_button,
                 "halign", GTK_ALIGN_END,
                 "valign", GTK_ALIGN_START,
                 NULL);
    g_object_set(self->save_button,
                 "halign", GTK_ALIGN_END,
                 "valign", GTK_ALIGN_START,
                 NULL);

    gtk_widget_add_css_class(self->close_button, "circular");
    gtk_widget_add_css_class(self->save_button, "circular");

    gtk_widget_set_margin_start(self->pref_container, 80);
    gtk_widget_set_margin_end(self->pref_container, 80);

    g_signal_connect(G_OBJECT(self->close_button), "clicked", G_CALLBACK(callback_close_button), self);
}