#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QTextEdit>

#include "../content_base.h"
#include "png_decoder.h"

class ImageAnalyzer : public ContentBase {
    private:
        QLabel* selected;
        QLabel* image_preview;
        QTextEdit* image_properties;
    public:
        ImageAnalyzer(QWidget* parent = NULL);
        void open_file_dialog();
};