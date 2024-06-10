/* l-device-concept.h
 *
 * Copyright 10.06.24 NordLex
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

#pragma once

#include <libadwaita-1/adwaita.h>


G_BEGIN_DECLS

#define L_TYPE_DEVICE_CONCEPT (l_device_concept_get_type())

G_DECLARE_FINAL_TYPE (LDeviceConcept, l_device_concept, L, DEVICE_CONCEPT, GObject)

LDeviceConcept *
l_device_concept_new(void);

G_END_DECLS
