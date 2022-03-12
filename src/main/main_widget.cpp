#include "main_widget.h"
#include "../menu/menu_widget.h"
#include "../content/content_holder.h"

MainWidget::MainWidget(QWidget* parent) : QWidget{parent} {
    this->resize(800, 600);
    this->setWindowTitle("Ultimate Geocache Tool");
    this->setWindowIcon(QIcon("../res/icon.svg"));
    this->setMinimumWidth(150);
    this->setMinimumHeight(200);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    ContentHolder* content = new ContentHolder();
    MenuWidget* menu = new MenuWidget(content);
    layout->addWidget(menu);
    layout->addWidget(content);
}