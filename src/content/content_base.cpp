#include "content_base.h"

ContentBase::ContentBase(QWidget* parent) : QWidget{parent}, id{ContentBase::max_id++} {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // define default style
    this->setStyleSheet("color:white;background-color:rgb(30, 30, 30);");
}

const int* ContentBase::get_id() {
    return &this->id;
}