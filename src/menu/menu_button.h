#pragma once

#include <QPushButton>
#include <QString>
#include <QObject>

#include "../content/content_holder.h"

class MenuButton : public QPushButton {
    /* Buttons for switching between content tabs */
    Q_OBJECT

    private:
        int id;
    public:
        static int max_id;

        MenuButton(QString icon_path, ContentHolder* content, QWidget* parent = NULL);
        const int* get_id();
        void handle_click();
    signals:
        void change_content(int id);
};