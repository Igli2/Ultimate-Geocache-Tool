#include "content_holder.h"

#include <iostream>

ContentHolder::ContentHolder(QWidget* parent) : QWidget{parent}, current_content_index{0} {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color:rgb(69, 69, 69);");

    this->layout = new QGridLayout(this);

    this->create_views();

    this->layout->addWidget(this->views.at(this->current_content_index));
}

ContentHolder::~ContentHolder() {
    for (ContentBase* ptr : this->views) {
        delete ptr;
    }
}

void ContentHolder::create_views() {
    SudokuWidget* sudoku = new SudokuWidget();
    this->views.push_back(sudoku);

    ImageAnalyzer* img = new ImageAnalyzer();
    this->views.push_back(img);
}

void ContentHolder::set_content(int index) {
    if (index == this->current_content_index) {
        return;
    }
    this->views.at(this->current_content_index)->setParent(NULL);
    this->layout->addWidget(this->views.at(index));
    this->current_content_index = index;
}