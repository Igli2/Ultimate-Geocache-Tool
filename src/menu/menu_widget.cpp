#include "menu_widget.h"

MenuWidget::MenuWidget(ContentHolder* content, QWidget* parent) : QWidget{parent} {
    this->setFixedWidth(64);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->setStyleSheet("background-color:rgb(37, 37, 37);");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);

    MenuButton* button = new MenuButton("../res/sudoku.svg", content);
    layout->addWidget(button);

    MenuButton* button2 = new MenuButton("../res/image.svg", content);
    layout->addWidget(button2);

    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer);
}