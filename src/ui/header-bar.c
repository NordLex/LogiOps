/* header-bar.c
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

#include "header-bar.h"

const char * HEADER_BAR_STYLE[] = {"flat"};

static void menu_button_clicked(void) {}

static GMenu * header_bar_menu(void) {
    GMenu * menu_app = g_menu_new();
    GMenu * sub_menu = g_menu_new();

    g_menu_append(menu_app, "Preferences", "app.preferences");
    g_menu_append(menu_app, "Keyboard Shortcuts", "win.show-help-overlay");
    g_menu_append(menu_app, "About", "app.about");
    g_menu_append(sub_menu, "Open config file", "app.about");
    g_menu_append(sub_menu, "Save config file", "app.about");
    g_menu_append(sub_menu, "Tutorial", "app.about");
    g_menu_append(sub_menu, "About", "app.about");
    g_menu_append_submenu(menu_app, "Sub Menu", (GMenuModel *) sub_menu);
    g_menu_append(menu_app, "Quit", "app.quit");

    return menu_app;
}

void set_l_header_bar(GtkWidget * header_bar) {
    GtkWidget * menu_button = gtk_menu_button_new();
    GtkWidget * title = adw_window_title_new(L_APP_NAME, NULL);
    GMenu * menu = header_bar_menu();

    g_object_set(menu_button,
                 "icon-name", "open-menu-symbolic",
                 "menu-model", (GMenuModel *) menu,
                 NULL);

    adw_header_bar_pack_end(ADW_HEADER_BAR(header_bar), GTK_WIDGET(menu_button));
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), GTK_WIDGET(title));

    gtk_widget_set_css_classes(GTK_WIDGET(header_bar), HEADER_BAR_STYLE);
}