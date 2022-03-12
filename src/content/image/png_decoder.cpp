#include "png_decoder.h"

PNGDecoder::PNGDecoder() {}

void PNGDecoder::decode(std::string file) {
    // FILE* image_stream = fopen(file.c_str(), "rb");
    std::ifstream image_stream;
    image_stream.open(file, std::ifstream::in | std::ifstream::binary);

    /* Check the first 8 bytes for the PNG signature */
    bool valid = this->decode_signature(image_stream);
    if (!valid) {
        std::cout << "Not a png file" << std::endl;
        return;
    }

    /* Next chunk identifier must be the header */
    this->decode_header(image_stream);
}

void PNGDecoder::decode_header(std::ifstream& image_stream) {
    /* Read the length of the chunks data */
    unsigned int length = this->get_uint(image_stream);

    /* Check the chunk type */
    char header_signature[4] = {'I', 'H', 'D', 'R'};
    char buf;
    for (int i = 0; i < 4; i++) {
        buf = '\0';
        image_stream.read(&buf, 1);
        if (buf != header_signature[i]) {
            throw std::invalid_argument("Missing PNG header");
        }
    }

    /* Read the chunk data */
    this->img_width = get_uint(image_stream);
    this->img_height = get_uint(image_stream);
    image_stream.read((char*)&this->img_bit_depth, 1);
    image_stream.read((char*)&this->img_color_type, 1);
    image_stream.read((char*)&this->img_compression_method, 1);
    image_stream.read((char*)&this->img_filter_method, 1);
    image_stream.read((char*)&this->img_interlace_method, 1);
    std::cout << this->img_width << " " << this->img_height << " " << this->img_bit_depth << " " << this->img_color_type << " " << this->img_compression_method << " " << this->img_filter_method << " " << this->img_interlace_method << std::endl;
}

bool PNGDecoder::decode_signature(std::ifstream& image_stream) {
    char signature[8] = {'\x89', 'P', 'N', 'G', '\x0D', '\x0A', '\x1A', '\x0A'};

    char buf;
    for (int i = 0; i < 8; i++) {
        buf = '\0';
        image_stream.read(&buf, 1);
        if (buf != signature[i]) {
            return false;
        }
    }

    return true;
}

unsigned int PNGDecoder::get_uint(std::ifstream& image_stream) {
    unsigned char bytes[4] = {0};
    image_stream.read((char*)bytes, 4);
    unsigned int value = bytes[3] | bytes[2] << 8 | bytes[1] << 16 | bytes[0] << 24;
    return value;
}