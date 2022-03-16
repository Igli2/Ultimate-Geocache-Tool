#include "menu_button.h"

int MenuButton::max_id = 0;

MenuButton::MenuButton(QString icon_path, ContentHolder* content, QWidget* parent) : QPushButton{parent}, id{MenuButton::max_id++} {
    this->setIcon(QIcon(icon_path));
    this->setIconSize(QSize(64, 64));

    connect(this, &QPushButton::released, this, &MenuButton::handle_click);
    connect(this, &MenuButton::change_content, content, &ContentHolder::set_content);
}


void MenuButton::handle_click() {
    emit this->change_content(this->id);
}