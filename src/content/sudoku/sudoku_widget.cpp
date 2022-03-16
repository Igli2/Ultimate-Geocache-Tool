#include "sudoku_widget.h"

SudokuWidget::SudokuWidget(QWidget* parent) : ContentBase{parent} {
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QHBoxLayout* options_layout = this->create_sudoku_options();
    main_layout->addLayout(options_layout);

    this->sudoku_grid = new SudokuGrid(this, NULL);
    main_layout->addWidget(this->sudoku_grid);

    this->error_label = new QLabel();
    this->error_label->setVisible(false);
    this->error_label->setStyleSheet("color:red;");
    main_layout->addWidget(this->error_label);

    QPushButton* solve_button = new QPushButton();
    solve_button->setText("Solve");
    main_layout->addWidget(solve_button);

    QSpacerItem* spacer = new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    main_layout->addSpacerItem(spacer);

    connect(this->size_select, &QComboBox::currentTextChanged, this->sudoku_grid, &SudokuGrid::on_size_selection_change);
    connect(solve_button, &QPushButton::released, this, &SudokuWidget::solve);
}

/* Check the inputs for validness and then call the actual sudoku solver */
// Parameters for solver: int size, std::vector<char> sudoku, std::string alphabet, std::vector<std::vector<int>> grid
void SudokuWidget::solve() {
    this->error_label->setVisible(false);

    int size = this->get_selected_size();
    QString alphabet = this->alphabet_edit->text();

    /* Check length */
    if (size != alphabet.length()) {
        this->error_label->setVisible(true);
        this->error_label->setText("Alphabet is too long / short");
        return;
    }

    /* Check for duplicates */
    for (QChar c : alphabet) {
        if (alphabet.count(c) > 1) {
            this->error_label->setVisible(true);
            this->error_label->setText("Alphabet contains duplicate characters");
            return;
        }
    }

    try {
        std::vector<QChar> unsolved_sudoku = this->sudoku_grid->sudoku_to_array(alphabet);
    } catch (const std::runtime_error& e) {
        this->error_label->setVisible(true);
        this->error_label->setText(e.what());
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





SudokuGrid::SudokuGrid(SudokuWidget* sudoku_widget, QWidget* parent) : QWidget{parent}, sudoku_widget{sudoku_widget} {
    this->sudoku_grid = new QGridLayout();
    this->sudoku_grid->setSpacing(5);
    this->sudoku_grid->setMargin(5);
    this->create_sudoku_grid();

    this->setLayout(this->sudoku_grid);
}

void SudokuGrid::create_sudoku_grid() {
    int size = this->sudoku_widget->get_selected_size();
    this->setFixedSize(30 * size + 5, 30 * size + 5);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            QLineEdit* field = new QLineEdit();
            field->setFixedSize(25, 25);
            field->setMaxLength(1);
            field->setStyleSheet("background-color:rgb(37, 37, 37);");
            this->sudoku_grid->addWidget(field, y, x);
            this->grid_fields.push_back(field);
        }
    }

    QSpacerItem* spacer_h = new QSpacerItem(0, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->sudoku_grid->addItem(spacer_h, 1, size);
}

/* Returns vector with QChars from grid or QChar::Null if line edit is empty */
std::vector<QChar> SudokuGrid::sudoku_to_array(QString& alphabet) {
    std::vector<QChar> v;
    for (QLineEdit* le : this->grid_fields) {
        QString text = le->text();
        if (!text.isEmpty()) {
            QChar c = text.at(0);
            if (alphabet.contains(c)) {
                v.push_back(c);
            } else {
                throw std::runtime_error("Invalid characters in grid");
            }
        } else {
            v.push_back(QChar::Null);
        }
    }
    return v;
}

/* Remove all LineEdits from the sudoku grid */
void SudokuGrid::clear_sudoku_grid() {
    this->grid_fields.clear();
    QLayoutItem* item;
    while ((item = this->sudoku_grid->layout()->takeAt(0)) != NULL) {
        delete item->widget();
        delete item;
    }
}

void SudokuGrid::on_size_selection_change() {
    this->clear_sudoku_grid();
    this->create_sudoku_grid();
}

/* Draw block lines in background */
void SudokuGrid::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    int lines = std::sqrt(this->sudoku_widget->get_selected_size());
    QPainter painter(this);

    QPen pen(QColor(255, 255, 255));
    pen.setWidth(3);
    painter.setPen(pen);

    for (int x = 0; x < lines - 1; x++) {
        double start = lines * 30 + 2.5;
        QLine line(start + x * lines * 30, 0.0, start + x * lines * 30, 30 * lines * lines + 5);
        painter.drawLine(line);

        QLine line2(0.0, start + x * lines * 30, 30 * lines * lines + 5, start + x * lines * 30);
        painter.drawLine(line2);
    }
}