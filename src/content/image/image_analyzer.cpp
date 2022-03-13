#include "image_analyzer.h"

ImageAnalyzer::ImageAnalyzer(QWidget* parent) : ContentBase{parent} {
    this->png_decoder = new PNGDecoder();

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
    this->image_properties->setText(QString("<h2><b>Image Properties</b></h2>"));
    layout->addWidget(this->image_properties);

    this->appended_data = new QTextEdit();
    this->appended_data->setReadOnly(true);
    this->appended_data->setText(QString("Appended data after IEND chunk\n\n"));
    layout->addWidget(this->appended_data);

    QPushButton* save_appended_data = new QPushButton();
    save_appended_data->setText("Save as...");
    save_appended_data->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(save_appended_data);

    QSpacerItem* spacer2 = new QSpacerItem(1, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer2);

    connect(select_file, &QPushButton::released, this, &ImageAnalyzer::open_file_dialog);
    connect(save_appended_data, &QPushButton::released, this, &ImageAnalyzer::save_file_dialog);
}

ImageAnalyzer::~ImageAnalyzer() {
    delete this->png_decoder;
}

/* Open a file dialog and select an image file, update image preview and labels */
void ImageAnalyzer::open_file_dialog() {
    QString file = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "*.png *.jpg *.jpeg");
    if (!file.isEmpty()) {
        this->selected->setText(file);
        this->image_preview->setPixmap(QPixmap(file).scaled(250, 250, Qt::KeepAspectRatio));

        this->decode_file(file);
    }
}

/* Save the appended data from png_decoder to the selected file if it is not empty */
void ImageAnalyzer::save_file_dialog() {
    QString file = QFileDialog::getSaveFileName(this, "Save As");

    if (!file.isEmpty() && !this->png_decoder->get_appended_data().empty()) {
        std::ofstream out_stream{file.toStdString()};
        out_stream << this->png_decoder->get_appended_data();
        out_stream.close();
    }
}

void ImageAnalyzer::decode_file(QString file) {
    this->png_decoder = new PNGDecoder();
    bool successful = this->png_decoder->decode(file.toStdString());
    if (!successful) {
        this->image_properties->setText("<h2><b>Image Properties</b></h2><br>Image format not supported.<br>");
        return;
    }

    /* Goal: http://fotoforensics.com/, something like that */
    /* Generate the text to display */
    std::stringstream text;

    text << "<h2><b>Image Properties</b></h2><br>";
    text << "Size: " << this->png_decoder->get_width() << "x" << this->png_decoder->get_height() << " (IHDR chunk)<br><br>";
    text << "Last Edited: " << this->png_decoder->get_last_edited() << " (tIME chunk)<br><br>";
    for (const std::string& s : this->png_decoder->get_text()) {
        text << s << " (tEXt/zTXt/iTXt chunk)<br><br>";
    }

    this->image_properties->setText(QString(text.str().c_str()));

    this->appended_data->setText(QString("Appended data after IEND chunk\n\n") + QString(this->png_decoder->get_appended_data().c_str()));
}