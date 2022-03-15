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
#include <iostream>

#include "../content_base.h"

class SudokuWidget : public ContentBase {
    private:
        QComboBox* size_select;
        QLineEdit* alphabet_edit;
        QGridLayout* sudoku_grid;

        QHBoxLayout* create_sudoku_options();
        void create_sudoku_grid();
        void on_size_selection_change();
        void clear_sudoku_grid();
        void solve();
        int get_selected_size();
    public:
        SudokuWidget(QWidget* parent = NULL);
};