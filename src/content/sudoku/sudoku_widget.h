#pragma once

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpacerItem>
#include <QCheckBox>
#include <QPushButton>
#include <QPainter>

#include <iostream>
#include <vector>
#include <cmath>

#include "../content_base.h"

class SudokuGrid;

class SudokuWidget : public ContentBase {
    private:
        QComboBox* size_select;
        QLineEdit* alphabet_edit;
        QLabel* error_label;
        SudokuGrid* sudoku_grid;

        QHBoxLayout* create_sudoku_options();
        void solve();
    public:
        SudokuWidget(QWidget* parent = NULL);
        int get_selected_size();
};

class SudokuGrid : public QWidget {
    private:
        QGridLayout* sudoku_grid;
        std::vector<QLineEdit*> grid_fields;
        SudokuWidget* sudoku_widget;

        void create_sudoku_grid();
        void clear_sudoku_grid();
        void paintEvent(QPaintEvent* event);
    public:
        SudokuGrid(SudokuWidget* sudoku_widget, QWidget* parent = NULL);
        void on_size_selection_change();
        std::vector<QChar> sudoku_to_array(QString& alphabet);
};