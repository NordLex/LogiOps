/* l-overview-page.c
 *
 * Copyright 18.11.2023 NordLex
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

#include "l-overview-page.h"

struct _LOverviewPage {
    GtkBox parent_instance;

    GtkWidget *carousel;
    GSList *card_list;
};

G_DEFINE_FINAL_TYPE(LOverviewPage, l_overview_page, GTK_TYPE_BOX)

static void
fill_cards(LOverviewPage *self) {
    GSList *cards = self->card_list;

    while (cards != NULL) {
        LDeviceCard *card = cards->data;
        adw_carousel_append(ADW_CAROUSEL(self->carousel), GTK_WIDGET(card));
        cards = g_slist_next(cards);
    }
}

LOverviewPage *
l_overview_page_new(GSList *cards) {
    LOverviewPage *self = g_object_new(L_TYPE_OVERVIEW_PAGE, NULL);
    self->card_list = cards;
    fill_cards(self);

    return self;
}

static void
l_overview_page_class_init(LOverviewPageClass *klass) {}

static void
l_overview_page_init(LOverviewPage *self) {
    self->carousel = adw_carousel_new();
    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->carousel));

    g_object_set(self,
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 0,
                 "hexpand", TRUE,
                 "vexpand", TRUE,
                 NULL);
}
