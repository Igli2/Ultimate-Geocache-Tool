CONFIG += debug
CONFIG += silent

HEADERS =   src/main/main_widget.h \
            src/menu/menu_widget.h \
            src/menu/menu_button.h \
            src/content/content_holder.h \
            src/content/content_base.h \
            src/content/image/image_analyzer.h \
            src/content/image/png_decoder.h \
            src/util/time.h

SOURCES =   src/main/app_launcher.cpp \
            src/main/main_widget.cpp \
            src/menu/menu_widget.cpp \
            src/menu/menu_button.cpp \
            src/content/content_holder.cpp \
            src/content/content_base.cpp \
            src/content/image/image_analyzer.cpp \
            src/content/image/png_decoder.cpp \
            src/util/time.cpp

QT += widgets

LIBS += -lboost_iostreams

TARGET = ultimate_geocache_tool