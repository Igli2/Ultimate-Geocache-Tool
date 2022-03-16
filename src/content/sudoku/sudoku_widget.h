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
#include <QCheckBox>

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
        QCheckBox* blocks_toggle;
        QCheckBox* grouping_mode;
        SudokuGrid* sudoku_grid;
        int filled_groups;
        int current_group;
        int size;

        QHBoxLayout* create_sudoku_options();
        void size_changed();
        void blocks_toggled();
        void solve();
    public:
        SudokuWidget(QWidget* parent = NULL);
        int get_selected_size();
        Qt::CheckState get_blocks_state();
        Qt::CheckState get_grouping_state();
        void reset_groupings();
        int next_group_id();
};

class SudokuField;

class SudokuGrid : public QWidget {
    private:
        QGridLayout* sudoku_grid;
        std::vector<SudokuField*> grid_fields;
        SudokuWidget* sudoku_widget;

        void create_sudoku_grid();
        void clear_sudoku_grid();
        void paintEvent(QPaintEvent* event);
    public:
        SudokuGrid(SudokuWidget* sudoku_widget, QWidget* parent = NULL);
        void on_size_selection_change();
        std::vector<QChar> sudoku_to_array(QString& alphabet);
};

class SudokuField : public QLineEdit {
    private:
        SudokuWidget* sudoku_widget;
        int group;

        void focusInEvent(QFocusEvent* event);
    public:
        SudokuField(SudokuWidget* sudoku_widget, QWidget* parent = NULL);
        int get_group();
        void set_group(int id);
};