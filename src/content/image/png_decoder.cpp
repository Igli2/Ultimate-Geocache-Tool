#include "png_decoder.h"

PNGDecoder::PNGDecoder() : last_edited{} {}

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

    /* Parse any chunk */
    std::string chunk_name = "....";
    while(chunk_name != "IEND") {
        unsigned int chunk_length = this->get_uint(image_stream);
        chunk_name = this->get_chunk_name(image_stream);
        if (chunk_name == "tIME") {
            /* length is always 7 */
            this->decode_time(image_stream);
        } else if (chunk_name == "IHDR") {
            /* length is always 13 */
            this->decode_header(image_stream);
        } else {
            /* Ignore chunk data for any other chunk */
            std::cout << chunk_length << " " << chunk_name << std::endl;
            for (unsigned int i = 0; i < chunk_length; i++) {
                this->get_byte(image_stream);
            }
        }
        this->get_uint(image_stream);
    }
}

void PNGDecoder::decode_time(std::ifstream& image_stream) {
    this->last_edited = {
        this->get_short(image_stream),
        (unsigned short) this->get_byte(image_stream),
        (unsigned short) this->get_byte(image_stream),
        (unsigned short) this->get_byte(image_stream),
        (unsigned short) this->get_byte(image_stream),
        (unsigned short) this->get_byte(image_stream)
    };
    std::cout << time_to_string(this->last_edited) << std::endl;
}

void PNGDecoder::decode_header(std::ifstream& image_stream) {
    /* Read the image attributes */
    this->img_width = this->get_uint(image_stream);
    this->img_height = this->get_uint(image_stream);
    this->img_bit_depth = this->get_byte(image_stream);
    this->img_color_type = this->get_byte(image_stream);
    this->img_compression_method = this->get_byte(image_stream);
    this->img_filter_method = this->get_byte(image_stream);
    this->img_interlace_method = this->get_byte(image_stream);
    std::cout << this->img_width << " " << this->img_height << " " << this->img_bit_depth << " " << this->img_color_type << " " << this->img_compression_method << " " << this->img_filter_method << " " << this->img_interlace_method << std::endl;
}

bool PNGDecoder::decode_signature(std::ifstream& image_stream) {
    char signature[8] = {'\x89', 'P', 'N', 'G', '\x0D', '\x0A', '\x1A', '\x0A'};

    char buf;
    for (int i = 0; i < 8; i++) {
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

unsigned int PNGDecoder::get_byte(std::ifstream& image_stream) {
    unsigned char byte = '\0';
    image_stream.read((char*)&byte, 1);
    return (unsigned int)byte;
}

unsigned short PNGDecoder::get_short(std::ifstream& image_stream) {
    unsigned char bytes[2] = {0};
    image_stream.read((char*)bytes, 2);
    unsigned short value = bytes[1] | bytes[0] << 8;
    return value;
}

std::string PNGDecoder::get_chunk_name(std::ifstream& image_stream) {
    std::string name = "....";
    char buf;
    for (int i = 0; i < 4; i++) {
        image_stream.read(&buf, 1);
        name[i] = buf;
    }
    return name;
}