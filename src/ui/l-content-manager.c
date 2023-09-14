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

    LConfReader *conf_reader;
    DeviceDescription *device_description;
    LDevicePage *device_page;
};

G_DEFINE_FINAL_TYPE (LContentManager, l_content_manager, G_TYPE_OBJECT)

static void
set_default_button_conf(gpointer *conf) {
    conf = NULL;
}

gpointer
find_conf_cid(gint cid, GSList *button_conf) {
    GSList *temp = button_conf;

    while (temp != NULL) {
        Button *conf = temp->data;
        if (conf->cid == cid) {
            return conf;
        }
        temp = g_slist_next(temp);
    }

    return NULL;
}

static void
attach_buttons_conf(GSList *buttons_conf, GSList *buttons_description) {
    GSList *temp = buttons_description;

    while (temp != NULL) {
        ButtonDescription *description = temp->data;
        gpointer *conf = find_conf_cid(description->cid, buttons_conf);
        if (conf != NULL) {
            description->conf = conf;
        } else {
            set_default_button_conf(description->conf);
        }
        temp = g_slist_next(temp);
    }
}

static void
set_device_description(LContentManager *self, gpointer device) {
    LDevice *device_conf = L_DEVICE(device);
    GSList *buttons_conf = l_device_get_buttons_conf(device_conf);

    self->device_description = description_mx_master_3();
    self->device_description->conf = device_conf;
    attach_buttons_conf(buttons_conf, self->device_description->buttons);
}

GtkWidget *
l_content_manager_get_content(LContentManager *self) {
    set_device_description(self, l_conf_reader_get_device(self->conf_reader));
    self->device_page = l_device_page_new(self->device_description);

    return GTK_WIDGET(self->device_page);
}

LContentManager *
l_content_manager_new(LConfReader *conf_reader) {
    LContentManager *manager = g_object_new(L_TYPE_CONTENT_MANAGER, NULL);

    manager->conf_reader = conf_reader;

    return manager;
}

static void
l_content_manager_class_init(LContentManagerClass *Klass) {}

static void
l_content_manager_init(LContentManager *self) {
    self->device_page = NULL;
    self->conf_reader = NULL;
}