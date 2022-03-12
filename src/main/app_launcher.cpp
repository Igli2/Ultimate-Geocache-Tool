#include <QApplication>

#include "main_widget.h"
#include "../content/content_base.h"
#include "../menu/menu_button.h"

int ContentBase::max_id = 0;
int MenuButton::max_id = 0;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWidget main;
    main.show();
    return app.exec();
}