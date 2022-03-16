#include "content_base.h"

int ContentBase::max_id = 0;

ContentBase::ContentBase(QWidget* parent) : QWidget{parent}, id{ContentBase::max_id++} {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // define default style
    this->setStyleSheet("color:white;background-color:rgb(30, 30, 30);");
}