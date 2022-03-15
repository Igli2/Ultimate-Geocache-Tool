#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QObject>

#include "content_base.h"
#include "image/image_analyzer.h"
#include "sudoku/sudoku_widget.h"

class ContentHolder : public QWidget {
    /* Layout for content management */
    Q_OBJECT

    private:
        int current_content_index;
        std::vector<ContentBase*> views;
        QGridLayout* layout;
        void create_views();
    public:
        ContentHolder(QWidget* parent = NULL);
        ~ContentHolder();
    public slots:
        void set_content(int index);
};