#include "menu_button.h"

#include <iostream>

MenuButton::MenuButton(QString icon_path, ContentHolder* content, QWidget* parent) : QPushButton{parent}, id{MenuButton::max_id++} {
    this->setIcon(QIcon(icon_path));
    this->setIconSize(QSize(64, 64));

    connect(this, &QPushButton::released, this, &MenuButton::handle_click);
    connect(this, &MenuButton::change_content, content, &ContentHolder::set_content);
}

const int* MenuButton::get_id() {
    return &this->id;
}

void MenuButton::handle_click() {
    emit this->change_content(this->id);
}