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

    GtkWidget * title;
    GtkWidget * pref_container;
    GtkWidget * apply_button;
};

G_DEFINE_FINAL_TYPE (LPrefPanel, l_pref_panel, GTK_TYPE_BOX)

typedef struct {
    gboolean *state;
    GtkWidget *expander;
} ExpanderSwitch;


static void callback_set_state(GtkSwitch *widget, gboolean state, gpointer data) {
    gboolean *settings_state = (gboolean *) data;

    *settings_state = state;
    gtk_switch_set_active(widget, *settings_state);
}

static void callback_set_sm_state(GtkSwitch *widget, gboolean state, gpointer data) {
    ExpanderSwitch *exp_switch = (ExpanderSwitch *) data;

    callback_set_state(widget, state, exp_switch->state);
    adw_expander_row_set_enable_expansion(ADW_EXPANDER_ROW(exp_switch->expander), state);
}

static void callback_set_value(GtkRange *widget, gpointer data) {
    gint *settings_value = (gint *) data;
    *settings_value = (gint) gtk_range_get_value(widget);
}

static void callback_apply_button_clicked(GtkWidget *button, gpointer data) {
    LPrefPanel *self = L_PREF_PANEL(data);
    g_object_set(G_OBJECT(self), "visible", FALSE, NULL);
}

static void l_pref_panel_init_apply_button(LPrefPanel *self) {
    GtkWidget * button_title = gtk_label_new("Close");
    GCallback on_click = G_CALLBACK(callback_apply_button_clicked);

    gtk_button_set_child(GTK_BUTTON(self->apply_button), button_title);
    g_signal_connect(G_OBJECT(self->apply_button), "clicked", on_click, self);
}

static void l_pref_panel_init_dpi(gint *dpi, GtkWidget *parent) {
    GtkWidget *dpi_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                200.0, 4000.0, 50.0);

    g_object_set(scale,
                 "hexpand", TRUE,
                 NULL);

    gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
    gtk_range_set_increments(GTK_RANGE(scale), 50.0, 500.0);
    gtk_range_set_value(GTK_RANGE(scale), (gdouble) *dpi);
    g_signal_connect(scale, "value-changed", G_CALLBACK(callback_set_value), dpi);
    gtk_box_append(GTK_BOX(dpi_box), scale);
    gtk_box_append(GTK_BOX(parent), dpi_box);
}

static void l_pref_panel_init_smartshift(Smartshift *smartshift, GtkWidget *parent) {
    ExpanderSwitch *exp_switch = g_malloc(sizeof(ExpanderSwitch));
    GtkWidget *row = adw_expander_row_new();
    GtkWidget *state_switch = gtk_switch_new();

    GtkWidget *threshold_row = adw_action_row_new();
    GtkWidget *threshold_label = gtk_label_new("Threshold");
    GtkWidget *threshold_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                          0, 100, 1);
    GtkWidget *torque_row = adw_action_row_new();
    GtkWidget *torque_label = gtk_label_new("Torque");
    GtkWidget *torque_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                       0, 100, 1);

    exp_switch->state = &smartshift->on;
    exp_switch->expander = row;
    g_object_set(state_switch, "valign", GTK_ALIGN_CENTER, NULL);

    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(row), "Smartshift");
    adw_expander_row_add_action(ADW_EXPANDER_ROW(row), state_switch);
    gtk_switch_set_active(GTK_SWITCH(state_switch), *exp_switch->state);
    adw_expander_row_set_enable_expansion(ADW_EXPANDER_ROW(row), *exp_switch->state);

    adw_action_row_add_prefix(ADW_ACTION_ROW(threshold_row), threshold_label);
    adw_action_row_add_suffix(ADW_ACTION_ROW(threshold_row), threshold_scale);
    adw_action_row_add_prefix(ADW_ACTION_ROW(torque_row), torque_label);
    adw_action_row_add_suffix(ADW_ACTION_ROW(torque_row), torque_scale);
    adw_expander_row_add_row(ADW_EXPANDER_ROW(row), threshold_row);
    adw_expander_row_add_row(ADW_EXPANDER_ROW(row), torque_row);

    gtk_widget_set_size_request(threshold_scale, 250, -1);
    gtk_widget_set_size_request(torque_scale, 250, -1);

    gtk_range_set_value(GTK_RANGE(threshold_scale), smartshift->threshold);
    gtk_range_set_value(GTK_RANGE(torque_scale), smartshift->torque);

    g_signal_connect(state_switch, "state-set", G_CALLBACK(callback_set_sm_state), exp_switch);
    g_signal_connect(threshold_scale, "value-changed", G_CALLBACK(callback_set_value), &smartshift->threshold);
    g_signal_connect(torque_scale, "value-changed", G_CALLBACK(callback_set_value), &smartshift->torque);

    gtk_box_append(GTK_BOX(parent), row);
}

static void l_pref_panel_init_hiresscroll(Hiresscroll *hiresscroll, GtkWidget *parent) {
    //GskRenderNode *node = gsk_blur_node_new();
    GtkWidget *row = adw_expander_row_new();
    GtkWidget *hires_row = adw_action_row_new();
    GtkWidget *hires_switch = gtk_switch_new();
    GtkWidget *invert_row = adw_action_row_new();
    GtkWidget *invert_switch = gtk_switch_new();
    GtkWidget *target_row = adw_action_row_new();
    GtkWidget *target_switch = gtk_switch_new();

    gboolean *hires_state = &hiresscroll->hires;
    gboolean *invert_state = &hiresscroll->invert;
    gboolean *target_state = &hiresscroll->target;

    adw_action_row_add_prefix(ADW_ACTION_ROW(hires_row), gtk_label_new("Hires"));
    adw_action_row_add_suffix(ADW_ACTION_ROW(hires_row), hires_switch);

    adw_action_row_add_prefix(ADW_ACTION_ROW(invert_row), gtk_label_new("Invert"));
    adw_action_row_add_suffix(ADW_ACTION_ROW(invert_row), invert_switch);

    adw_action_row_add_prefix(ADW_ACTION_ROW(target_row), gtk_label_new("Target"));
    adw_action_row_add_suffix(ADW_ACTION_ROW(target_row), target_switch);

    g_object_set(hires_switch, "valign", GTK_ALIGN_CENTER, NULL);
    g_object_set(invert_switch, "valign", GTK_ALIGN_CENTER, NULL);
    g_object_set(target_switch, "valign", GTK_ALIGN_CENTER, NULL);

    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(row), "Hiresscroll");
    adw_expander_row_add_row(ADW_EXPANDER_ROW(row), hires_row);
    adw_expander_row_add_row(ADW_EXPANDER_ROW(row), invert_row);
    adw_expander_row_add_row(ADW_EXPANDER_ROW(row), target_row);

    gtk_switch_set_active(GTK_SWITCH(hires_switch), *hires_state);
    gtk_switch_set_active(GTK_SWITCH(invert_switch), *invert_state);
    gtk_switch_set_active(GTK_SWITCH(target_switch), *target_state);

    g_signal_connect(hires_switch, "state-set", G_CALLBACK(callback_set_state), hires_state);
    g_signal_connect(invert_switch, "state-set", G_CALLBACK(callback_set_state), invert_state);
    g_signal_connect(target_switch, "state-set", G_CALLBACK(callback_set_state), target_state);

    gtk_box_append(GTK_BOX(parent), row);
}

static void l_pref_panel_clear_content(GtkWidget *container) {
    GtkWidget *child = gtk_widget_get_first_child(container);
    while (child != NULL) {
        gtk_box_remove(GTK_BOX(container), child);
        child = gtk_widget_get_first_child(container);
    }
}

static void l_pref_panel_init_content(LPrefPanel * self, gpointer button_conf) {
    LDevice *device = L_DEVICE(button_conf);
    GString *name = l_device_get_name(device);
    gint *dpi = l_device_get_dpi(device);
    Smartshift *smartshift = l_device_get_smartshift(device);
    Hiresscroll *hiresscroll = l_device_get_hiresscroll(device);

    gtk_label_set_markup(GTK_LABEL(self->title), name->str);
    l_pref_panel_clear_content(self->pref_container);
    l_pref_panel_init_dpi(dpi, self->pref_container);
    l_pref_panel_init_smartshift(smartshift, self->pref_container);
    l_pref_panel_init_hiresscroll(hiresscroll, self->pref_container);
}

void l_pref_panel_centered(LPrefPanel *self, int width) {
    g_object_set(self,
                 "halign", GTK_ALIGN_CENTER,
                 "valign", GTK_ALIGN_START,
                 NULL);
    gtk_widget_set_size_request(GTK_WIDGET(self), (int) (width * 0.7), -1);
}

void l_pref_panel_expand(LPrefPanel *self) {
    g_object_set(self,
                 "halign", FALSE,
                 "valign", FALSE,
                 NULL);
}

void l_pref_panel_configure(LPrefPanel * self, gpointer button_conf) {
    l_pref_panel_init_content(self, button_conf);
    l_pref_panel_init_apply_button(self);
}

LPrefPanel * l_pref_panel_new(void) {
    return g_object_new(L_TYPE_PREF_PANEL, NULL);
}

static void l_pref_panel_class_init(LPrefPanelClass * klass) {}

static void l_pref_panel_init(LPrefPanel * self) {
    self->title = gtk_label_new(NULL);
    self->pref_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->apply_button = gtk_button_new();

    gtk_box_append(GTK_BOX(self), self->title);
    gtk_box_append(GTK_BOX(self), self->pref_container);
    gtk_box_append(GTK_BOX(self), self->apply_button);

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
    g_object_set(self->title,
                 "halign", GTK_ALIGN_CENTER,
                 NULL);
    g_object_set(self->pref_container,
                 "vexpand", TRUE,
                 "hexpand", TRUE,
                 NULL);

    gtk_widget_set_margin_start(self->apply_button, 60);
    gtk_widget_set_margin_end(self->apply_button, 60);
    gtk_widget_set_margin_start(self->pref_container, 5);
    gtk_widget_set_margin_end(self->pref_container, 5);
}