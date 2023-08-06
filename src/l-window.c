/* logiops-window.c
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

#include "l-window.h"
#include "ui/header-bar.h"
#include "ui/l-content-manager.h"


struct _LWindow {
    AdwApplicationWindow parent_instance;

    LContentManager * content_manager;
    GtkWidget * header_bar;
};

G_DEFINE_FINAL_TYPE (LWindow, l_window, ADW_TYPE_APPLICATION_WINDOW)

static void l_window_set_css_style(void) {
    GtkCssProvider * provider = gtk_css_provider_new();
    GdkDisplay * display = gdk_display_get_default();

    gtk_css_provider_load_from_resource(provider, L_CSS_STYLE_PATH);
    gtk_style_context_add_provider_for_display(GDK_DISPLAY(display),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static void l_window_class_init(LWindowClass *klass) {}

static void l_window_init(LWindow *self) {
    GtkWidget * window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget * content_box;
    gtk_window_set_default_size(GTK_WINDOW(self), 1200, 700);

    self->header_bar = adw_header_bar_new();
    self->content_manager = l_content_manager_new();
    content_box = l_content_manager_get_content(self->content_manager);

    l_window_set_css_style();
    set_l_header_bar(self->header_bar);

    gtk_box_append(GTK_BOX(window_box), GTK_WIDGET(self->header_bar));
    gtk_box_append(GTK_BOX(window_box), GTK_WIDGET(content_box));

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(self),
                                       GTK_WIDGET(window_box));
}
