//
// Created by nordlex on 26.07.2023.
//

#include "header-bar.h"

const char * HEADER_BAR_STYLE[] = {"flat"};

void set_l_header_bar(GtkWidget * header_bar) {
    gtk_widget_set_css_classes(GTK_WIDGET(header_bar), HEADER_BAR_STYLE);
}