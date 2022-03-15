#include "sudoku_widget.h"

SudokuWidget::SudokuWidget(QWidget* parent) : ContentBase{parent} {
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QHBoxLayout* options_layout = this->create_sudoku_options();
    main_layout->addLayout(options_layout);


    this->sudoku_grid = new QGridLayout();
    this->create_sudoku_grid();
    main_layout->addLayout(this->sudoku_grid);

    QPushButton* solve_button = new QPushButton();
    solve_button->setText("Solve");
    main_layout->addWidget(solve_button);

    QSpacerItem* spacer = new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    main_layout->addSpacerItem(spacer);

    connect(this->size_select, &QComboBox::currentTextChanged, this, &SudokuWidget::on_size_selection_change);
    connect(solve_button, &QPushButton::released, this, &SudokuWidget::solve);
}

/* Check the inputs for validness and then call the actual sudoku solver */
void SudokuWidget::solve() {
    int size = this->get_selected_size();
    QString alphabet = this->alphabet_edit->text();

    /* Check length */
    if (size != alphabet.length()) {
        std::cout << "Alphabet is too long / short" << std::endl;
        return;
    }

    /* Check for duplicates */
    for (QChar c : alphabet) {
        if (alphabet.count(c) > 1) {
            std::cout << "Alphabet contains duplicate characters" << std::endl;
            return;
        }
    }
}

void SudokuWidget::on_size_selection_change() {
    this->clear_sudoku_grid();
    this->create_sudoku_grid();
}

/* Remove all LineEdits from the sudoku grid */
void SudokuWidget::clear_sudoku_grid() {
    QLayoutItem* item;
    while ((item = this->sudoku_grid->layout()->takeAt(0)) != NULL) {
        delete item->widget();
        delete item;
    }
}

/* Return the selected size in the size combo box as integer */
int SudokuWidget::get_selected_size() {
    QString current = this->size_select->currentText();
    int size = 0;
    if (current == "9x9") {
        size = 9;
    } else if (current == "16x16") {
        size = 16;
    } else {
        size = 25;
    }

    return size;
}

void SudokuWidget::create_sudoku_grid() {
    int size = this->get_selected_size();

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            QLineEdit* field = new QLineEdit();
            field->setFixedSize(25, 25);
            field->setMaxLength(1);
            field->setStyleSheet("background-color:rgb(37, 37, 37);");
            this->sudoku_grid->addWidget(field, y, x);
        }
    }

    QSpacerItem* spacer_v = new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem* spacer_h = new QSpacerItem(0, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->sudoku_grid->addItem(spacer_h, 1, size);
    this->sudoku_grid->addItem(spacer_v, size, 1);
}

QHBoxLayout* SudokuWidget::create_sudoku_options() {
    QHBoxLayout* layout = new QHBoxLayout();

    QLabel* size_label = new QLabel();
    size_label->setText("Size");
    layout->addWidget(size_label);

    this->size_select = new QComboBox();
    this->size_select->addItem("9x9");
    this->size_select->addItem("16x16");
    this->size_select->addItem("25x25");
    layout->addWidget(this->size_select);

    QLabel* alphabet_label = new QLabel();
    alphabet_label->setText("Alphabet");
    layout->addWidget(alphabet_label);

    this->alphabet_edit = new QLineEdit();
    this->alphabet_edit->setPlaceholderText("123456789/abcdefghijklmnop/...");
    layout->addWidget(this->alphabet_edit);

    return layout;
}