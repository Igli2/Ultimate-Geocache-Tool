#include "image_analyzer.h"

ImageAnalyzer::ImageAnalyzer(QWidget* parent) : ContentBase{parent} {
    QVBoxLayout* layout = new QVBoxLayout(this);

    /* Start select file layout */
    QHBoxLayout* select_layout = new QHBoxLayout();

    QPushButton* select_file = new QPushButton();
    select_file->setText("Select Image...");
    select_layout->addWidget(select_file);

    this->selected = new QLabel();
    this->selected->setText("No Image Selected...");
    select_layout->addWidget(this->selected);

    QSpacerItem* spacer = new QSpacerItem(0, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    select_layout->addSpacerItem(spacer);
    /* End select file layout */

    layout->addLayout(select_layout);

    this->image_preview = new QLabel();
    layout->addWidget(this->image_preview);

    this->image_properties = new QTextEdit();
    this->image_properties->setReadOnly(true);
    layout->addWidget(this->image_properties);

    QSpacerItem* spacer2 = new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer2);

    connect(select_file, &QPushButton::released, this, &ImageAnalyzer::open_file_dialog);
}

void ImageAnalyzer::open_file_dialog() {
    /* Open a file dialog and select an image file, update image preview and labels */
    QString file = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "*.png *.jpg *.jpeg");
    if (!file.isEmpty()) {
        this->selected->setText(file);
        this->image_preview->setPixmap(QPixmap(file).scaled(250, 250, Qt::KeepAspectRatio));

        PNGDecoder png_decoder;
        png_decoder.decode(file.toStdString());

        /* Generate the text to display */
        std::string text = "";
        text.append("Last Edited: ");
        text.append(png_decoder.get_last_edited());
        text.append("\n");
        for (const std::string& s : png_decoder.get_text()) {
            text.append(s);
            text.append("\n");
        }

        this->image_properties->setText(QString(text.c_str()));
    }
}