#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QCoreApplication>

#include "menu_button.h"
#include "../content/content_holder.h"

class MenuWidget : public QWidget {
    /* Layout for the Menu Buttons */
    public:
        MenuWidget(ContentHolder* content, QWidget* parent = NULL);
};