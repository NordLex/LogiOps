/* l-key-code.c
 *
 * Copyright 26.02.24 NordLex
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

#include "l-key-code.h"

typedef struct {
    char *kernel;
    guint gdk;
} KeyCode;

KeyCode codes[] = {
        (KeyCode) {"KEY_ESC",        GDK_KEY_Escape},
        (KeyCode) {"KEY_DELETE",     GDK_KEY_Delete},
        (KeyCode) {"KEY_1",          GDK_KEY_1},
        (KeyCode) {"KEY_2",          GDK_KEY_2},
        (KeyCode) {"KEY_3",          GDK_KEY_3},
        (KeyCode) {"KEY_4",          GDK_KEY_4},
        (KeyCode) {"KEY_5",          GDK_KEY_5},
        (KeyCode) {"KEY_6",          GDK_KEY_6},
        (KeyCode) {"KEY_7",          GDK_KEY_7},
        (KeyCode) {"KEY_8",          GDK_KEY_8},
        (KeyCode) {"KEY_9",          GDK_KEY_9},
        (KeyCode) {"KEY_0",          GDK_KEY_0},
        (KeyCode) {"KEY_MINUS",      GDK_KEY_minus},
        (KeyCode) {"KEY_EQUAL",      GDK_KEY_equal},
        (KeyCode) {"KEY_BACKSPACE",  GDK_KEY_BackSpace},
        (KeyCode) {"KEY_TAB",        GDK_KEY_Tab},
        (KeyCode) {"KEY_LEFTSHIFT",  GDK_KEY_Shift_L},
        (KeyCode) {"KEY_RIGHTSHIFT", GDK_KEY_Shift_R},
        (KeyCode) {"KEY_LEFTCTRL",   GDK_KEY_Control_L},
        (KeyCode) {"KEY_RIGHTCTRL",  GDK_KEY_Control_R},
        (KeyCode) {"KEY_LEFTALT",    GDK_KEY_Alt_L},
        (KeyCode) {"KEY_RIGHTALT",   GDK_KEY_Alt_R},
        (KeyCode) {"KEY_F1",         GDK_KEY_F1},
        (KeyCode) {"KEY_F2",         GDK_KEY_F2},
        (KeyCode) {"KEY_F3",         GDK_KEY_F3},
        (KeyCode) {"KEY_F4",         GDK_KEY_F4},
        (KeyCode) {"KEY_F5",         GDK_KEY_F5},
        (KeyCode) {"KEY_F6",         GDK_KEY_F6},
        (KeyCode) {"KEY_F7",         GDK_KEY_F7},
        (KeyCode) {"KEY_F8",         GDK_KEY_F8},
        (KeyCode) {"KEY_F9",         GDK_KEY_F9},
        (KeyCode) {"KEY_F10",        GDK_KEY_F10},
        (KeyCode) {"KEY_F11",        GDK_KEY_F11},
        (KeyCode) {"KEY_F12",        GDK_KEY_F12},
};

struct _LKeyCode {
    GObject parent_instance;

    GHashTable *kernel_to_gdk;
    GHashTable *gdk_to_kernel;
};

G_DEFINE_FINAL_TYPE(LKeyCode, l_key_code, G_TYPE_OBJECT)


static void
init_codes_tables(LKeyCode *self) {
    int iter = 0;

    while (iter < (sizeof codes / sizeof(KeyCode))) {
        char **kernel = &codes[iter].kernel;
        guint *gdk = &codes[iter].gdk;

        g_hash_table_insert(self->kernel_to_gdk,*kernel,gdk);
        g_hash_table_insert(self->gdk_to_kernel,gdk,kernel);

        iter++;
    }
}

void *
l_key_code_kernel_to_gdk(LKeyCode *self, char *key) {
    guint *gdk_key = g_hash_table_lookup(self->kernel_to_gdk, key);
    return gdk_key;
}

void *
l_key_code_gdk_to_kernel(LKeyCode *self, guint key) {
    char **kernel_key = g_hash_table_lookup(self->gdk_to_kernel, &key);
    return kernel_key;
}

LKeyCode *
l_key_code_new(void) {
    return g_object_new(L_TYPE_KEY_CODE, NULL);
}

static void
l_key_code_class_init(LKeyCodeClass *klass) {}

static void
l_key_code_init(LKeyCode *self) {
    self->kernel_to_gdk = g_hash_table_new(g_str_hash, g_str_equal);
    self->gdk_to_kernel = g_hash_table_new(g_int_hash, g_int_equal);
    init_codes_tables(self);
}
