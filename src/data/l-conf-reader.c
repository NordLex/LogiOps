/* l-conf-reader.c
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

#include "l-conf-reader.h"

struct _LConfReader {
    GObject parent_instance;

    config_t *cfg;
};

G_DEFINE_FINAL_TYPE (LConfReader, l_conf_reader, G_TYPE_OBJECT)

static void l_conf_reader_read(LConfReader *self, const char *file_name) {

}

LConfReader *
l_conf_reader_new(void) {
    return g_object_new(L_TYPE_CONF_READER, NULL);
}

static void
l_conf_reader_class_init(LConfReaderClass *klass) {}

static void
l_conf_reader_init(LConfReader *self) {
    config_init(self->cfg);
}