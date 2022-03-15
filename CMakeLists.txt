project(ultimate_geocache_tool)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ultimate_geocache_tool
    src/main/main_widget.h
    src/menu/menu_widget.h
    src/menu/menu_button.h
    src/content/content_holder.h
    src/content/content_base.h
    src/content/image/image_analyzer.h
    src/content/image/png_decoder.h
    src/content/sudoku/sudoku_widget.h

    src/main/app_launcher.cpp
    src/main/main_widget.cpp
    src/menu/menu_widget.cpp
    src/menu/menu_button.cpp
    src/content/content_holder.cpp
    src/content/content_base.cpp
    src/content/image/image_analyzer.cpp
    src/content/image/png_decoder.cpp
    src/content/sudoku/sudoku_widget.cpp
)

target_link_libraries(ultimate_geocache_tool Qt5::Widgets)
