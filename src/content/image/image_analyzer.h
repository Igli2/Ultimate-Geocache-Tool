#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QTextEdit>
#include <sstream>

#include "../content_base.h"
#include "png_decoder.h"

class ImageAnalyzer : public ContentBase {
    private:
        QLabel* selected;
        QLabel* image_preview;
        QTextEdit* image_properties;
        QTextEdit* appended_data;
        PNGDecoder* png_decoder;

        void decode_file(QString file);
        void open_file_dialog();
        void save_file_dialog();
    public:
        ImageAnalyzer(QWidget* parent = NULL);
        ~ImageAnalyzer();
};