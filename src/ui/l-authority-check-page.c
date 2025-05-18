/* l-authority-check-page.c
 *
 * Copyright 18.05.25 NordLex
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

#include "l-authority-check-page.h"


struct _LAuthorityCheckPage {
    GtkBox parent_instance;

    GtkWidget *pre_check;
    GtkWidget *post_check;
};

G_DEFINE_FINAL_TYPE (LAuthorityCheckPage, l_authority_check_page, GTK_TYPE_BOX)

static gboolean
check_authorization(void) {
    PolkitAuthority *authority;
    PolkitSubject *subject;
    PolkitAuthorizationResult *result;
    GError *error = NULL;
    gboolean is_authorized = FALSE;

    authority = polkit_authority_get_sync(NULL, &error);
    if (authority == NULL) {
        g_warning("Error getting polkit authority: %s", error->message);
        g_error_free(error);
        return FALSE;
    }

    subject = polkit_unix_process_new_for_owner(getpid(), 0, -1);

    result = polkit_authority_check_authorization_sync(
            authority,
            subject,
            L_POLKIT_ACTION_ID,
            NULL,
            POLKIT_CHECK_AUTHORIZATION_FLAGS_ALLOW_USER_INTERACTION,
            NULL,
            &error
    );

    if (error != NULL) {
        g_warning("Error checking authorization: %s", error->message);
        g_error_free(error);
    } else {
        is_authorized = polkit_authorization_result_get_is_authorized(result);
    }

    g_object_unref(result);
    g_object_unref(subject);
    g_object_unref(authority);

    return is_authorized;
}


LAuthorityCheckPage *
l_authority_check_page_new(void) {
    return g_object_new(L_TYPE_AUTHORITY_CHECK_PAGE, NULL);
}

static void
l_authority_check_page_class_init(LAuthorityCheckPageClass *klass) {}

static void
l_authority_check_page_init(LAuthorityCheckPage *self) {
    self->pre_check = gtk_label_new("The application requires superuser rights to operate!");
    self->post_check = gtk_label_new("Superuser rights successfully obtained!");

    gtk_box_append(GTK_BOX(self), GTK_WIDGET(self->pre_check));

    g_object_set(self,
                 "orientation", GTK_ORIENTATION_VERTICAL,
                 "spacing", 0,
                 "hexpand", TRUE,
                 "vexpand", TRUE,
                 NULL);
}
