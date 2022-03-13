#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <chrono>
#include <QDateTime>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

class PNGDecoder {
    private:
        unsigned int img_width;
        unsigned int img_height;
        unsigned int img_bit_depth;
        unsigned int img_color_type;
        unsigned int img_compression_method;
        unsigned int img_filter_method;
        unsigned int img_interlace_method;
        QDateTime last_edited;
        std::vector<std::string> text;
        std::string appended_data;

        bool decode_signature(std::ifstream& image_stream);
        void decode_header(std::ifstream& image_stream);
        void decode_time(std::ifstream& image_stream);
        void decode_text(std::ifstream& image_stream, unsigned int chunk_length);
        void decode_compressed_text(std::ifstream& image_stream, unsigned int chunk_length);
        void decode_appended_data(std::ifstream& image_stream);
        std::string get_chunk_name(std::ifstream& image_stream);
        // TODO: move to base class
        unsigned int get_uint(std::ifstream& image_stream);
        unsigned char get_byte(std::ifstream& image_stream);
        unsigned short get_short(std::ifstream& image_stream);
    public:
        PNGDecoder();
        bool decode(std::string file);
        std::string get_last_edited();
        const std::vector<std::string>& get_text();
        unsigned int get_width();
        unsigned int get_height();
        std::string get_appended_data();
};