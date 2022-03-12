#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>

class PNGDecoder {
    private:
        unsigned int img_width;
        unsigned int img_height;
        unsigned int img_bit_depth;
        unsigned int img_color_type;
        unsigned int img_compression_method;
        unsigned int img_filter_method;
        unsigned int img_interlace_method;

        bool decode_signature(std::ifstream& image_stream);
        void decode_header(std::ifstream& image_stream);
        unsigned int get_uint(std::ifstream& image_stream);
    public:
        PNGDecoder();
        void decode(std::string file);
};