#pragma once

#include <QWidget>

class ContentBase : public QWidget {
    private:
        int id;
    public:
        static int max_id;

        ContentBase(QWidget* parent = NULL);
};