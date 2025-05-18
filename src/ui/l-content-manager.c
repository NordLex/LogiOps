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

    LDataManager *data_manager;
    LOverviewPage *overview_page;
    LAuthorityCheckPage *authority_check_page;
    GtkWidget *back_button;
    GtkWidget *main_box;
    GSList *devices;
    GSList *device_cards;
};

G_DEFINE_FINAL_TYPE (LContentManager, l_content_manager, G_TYPE_OBJECT)


static void
return_callback(GtkWidget *widget, gpointer data) {
    LContentManager *manager = L_CONTENT_MANAGER(data);
    gtk_stack_set_visible_child_name(GTK_STACK(manager->main_box), "start-page");
    gtk_widget_set_visible(manager->back_button, FALSE);
}

static void
card_selected_callback(LDeviceCard *card, gpointer data) {
    LContentManager *manager = L_CONTENT_MANAGER(data);
    DeviceDescription *description = l_device_card_get_description(card);
    GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(manager->main_box),
                                                   description->name->str);

    if (NULL == child) {
        GtkWidget *device_page = l_device_page_new(description);
        gtk_stack_add_named(GTK_STACK(manager->main_box),
                            device_page,
                            description->name->str);
    }
    gtk_stack_set_visible_child_name(GTK_STACK(manager->main_box),
                                     description->name->str);
    gtk_widget_set_visible(manager->back_button, TRUE);
}

static GSList *
fill_cards(LContentManager *self) {
    GSList *cards = NULL;
    GSList *temp_devices = self->devices;

    while (temp_devices != NULL) {
        DeviceDescription *description = temp_devices->data;
        LDeviceCard *card = l_device_card_new(description);
        cards = g_slist_append(cards, card);
        g_signal_connect(card, "selected", G_CALLBACK(card_selected_callback), self);

        temp_devices = g_slist_next(temp_devices);
    }
    return cards;
}

static GtkWidget *
get_authority_check_page(LContentManager *self) {
    self->authority_check_page = l_authority_check_page_new();

    return GTK_WIDGET(self->authority_check_page);
}

static GtkWidget *
get_start_page(LContentManager *self) {
    self->device_cards = fill_cards(self);
    self->overview_page = l_overview_page_new(self->device_cards);

    return GTK_WIDGET(self->overview_page);
}

GtkWidget *
l_content_manager_get_content(LContentManager *self) {
    //self->devices = l_data_manager_get_devices_list(self->data_manager,
    //                                                self->devices);
    gtk_stack_add_named(GTK_STACK(self->main_box),
                        get_authority_check_page(self),
                        "authority-check-page");

    return GTK_WIDGET(self->main_box);
}

LContentManager *
l_content_manager_new(LDataManager *data_manager, GtkWidget *header_bar) {
    LContentManager *manager = g_object_new(L_TYPE_CONTENT_MANAGER, NULL);

    manager->data_manager = data_manager;

    adw_header_bar_pack_start(ADW_HEADER_BAR(header_bar), manager->back_button);

    return manager;
}

static void
l_content_manager_class_init(LContentManagerClass *Klass) {}

static void
l_content_manager_init(LContentManager *self) {
    self->main_box = gtk_stack_new();
    self->back_button = gtk_button_new_from_icon_name("go-previous-symbolic");

    self->devices = g_slist_append(self->devices, description_mx_master_3());
    self->devices = g_slist_append(self->devices, description_mx_anywhere_3());

    gtk_stack_set_transition_type(GTK_STACK(self->main_box),
                                  GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(self->main_box), 50);
    gtk_widget_set_visible(GTK_WIDGET(self->back_button), FALSE);

    g_signal_connect(self->back_button, "clicked", G_CALLBACK(return_callback), self);
}