//
// Created by nordlex on 26.07.2023.
//

#pragma once

#include "../l-application-resources.h"

G_BEGIN_DECLS

#define L_TYPE_CONTENT_MANAGER (l_content_manager_get_type())

G_DECLARE_FINAL_TYPE (LContentManager, l_content_manager, L, CONTENT_MANAGER, GObject)

LContentManager * l_content_manager_new(void);

GtkWidget * l_content_manager_get_content(LContentManager * self);

G_END_DECLS