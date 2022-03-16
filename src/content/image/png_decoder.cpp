#include "png_decoder.h"

PNGDecoder::PNGDecoder() {}

/* https://www.nayuki.io/page/png-file-chunk-inspector 
 * Use this tool to verify correctness of code */
bool PNGDecoder::decode(std::string file) {
    std::ifstream image_stream;
    image_stream.open(file, std::ifstream::in | std::ifstream::binary);

    /* Check the first 8 bytes for the PNG signature */
    bool valid = this->decode_signature(image_stream);
    if (!valid) {
        std::cout << "Not a png file" << std::endl;
        return false;
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
        } else if(chunk_name == "tEXt") {
            this->decode_text(image_stream, chunk_length);
        } else if (chunk_name == "zTXt") {
            this->decode_compressed_text(image_stream, chunk_length);
        } else {
            /* Ignore chunk data for any other chunk (non-standard chunks?! -> display extra) */
            // std::cout << chunk_length << " " << chunk_name << std::endl;
            for (unsigned int i = 0; i < chunk_length; i++) {
                this->get_byte(image_stream);
            }
        }
        this->get_uint(image_stream);
    }
    this->decode_appended_data(image_stream);

    return true;
}

/* Function to read all data until EOF into the appended data string */
void PNGDecoder::decode_appended_data(std::ifstream& image_stream) {
    std::stringstream out_stream;
    char c;
    while (true) {
        image_stream.read(&c, 1);
        if (image_stream.eof()) {
            break;
        }
        out_stream << c;
    }
    this->appended_data = out_stream.str();
}

/* Function for reading the data segment of a zTXt chunk and decode it using zlib inflate/deflate if compressed */
void PNGDecoder::decode_compressed_text(std::ifstream& image_stream, unsigned int chunk_length) {
    std::stringstream stream;

    char c = '\0';
    while ((c = this->get_byte(image_stream)) != '\0') {
        stream << c;
        chunk_length--;
    }
    stream << ": ";
    chunk_length--;

    unsigned int compression_method = this->get_byte(image_stream);
    chunk_length--;
    if (compression_method != 0) {
        std::cout << "Not a standard compression method" << std::endl;
    }

    std::stringstream compressed;
    std::stringstream decompressed;
    while (chunk_length-- > 0) {
        compressed << this->get_byte(image_stream);
    }

    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_decompressor());
    out.push(compressed);
    boost::iostreams::copy(out, decompressed);

    std::cout << "###" << decompressed.str() << "###" << std::endl;
    // if exif data is found:
    // https://exifdata.com/exif.php
    // https://stackoverflow.com/questions/1821515/how-is-exif-info-encoded
    // 45 78 69 66 00 00 (start of exif chunk)
}

/* Function for reading the data segment of a tEXt chunk */
void PNGDecoder::decode_text(std::ifstream& image_stream, unsigned int chunk_length) {
    std::stringstream stream;

    char c;
    while ((c = this->get_byte(image_stream)) != '\0') {
        stream << c;
        chunk_length--;
    }
    stream << ": ";
    chunk_length--;
    while (chunk_length-- > 0) {
        stream << this->get_byte(image_stream);
    }

    this->text.push_back(stream.str());
}

/* Function for reading the data segment of a tIME chunk */
void PNGDecoder::decode_time(std::ifstream& image_stream) {
    unsigned short year = this->get_short(image_stream);
    unsigned short month = this->get_byte(image_stream);
    unsigned short day = this->get_byte(image_stream);
    unsigned short hour = this->get_byte(image_stream);
    unsigned short minute = this->get_byte(image_stream);
    unsigned short second = this->get_byte(image_stream);

    this->last_edited.setDate(QDate(year, month, day));
    this->last_edited.setTime(QTime(hour, minute, second));
}

/* Function for reading the data segment of a IHDR chunk */
void PNGDecoder::decode_header(std::ifstream& image_stream) {
    this->img_width = this->get_uint(image_stream);
    this->img_height = this->get_uint(image_stream);
    this->img_bit_depth = this->get_byte(image_stream);
    this->img_color_type = this->get_byte(image_stream);
    this->img_compression_method = this->get_byte(image_stream);
    this->img_filter_method = this->get_byte(image_stream);
    this->img_interlace_method = this->get_byte(image_stream);
}

/* Function for reading the first 8 bits of the file to check if it is actually a .png file */
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

/* Get the next 4 bytes from image_stream as integer */
unsigned int PNGDecoder::get_uint(std::ifstream& image_stream) {
    unsigned char bytes[4] = {};
    image_stream.read((char*)bytes, 4);
    unsigned int value = bytes[3] | bytes[2] << 8 | bytes[1] << 16 | bytes[0] << 24;
    return value;
}

/* Get the next byte from image_stream as char */
unsigned char PNGDecoder::get_byte(std::ifstream& image_stream) {
    unsigned char byte = '\0';
    image_stream.read((char*)&byte, 1);
    return byte;
}

/* Get the next 2 bytes from image_stream as short */
unsigned short PNGDecoder::get_short(std::ifstream& image_stream) {
    unsigned char bytes[2] = {};
    image_stream.read((char*)bytes, 2);
    unsigned short value = bytes[1] | bytes[0] << 8;
    return value;
}

/* Get the next 4 bytes from image_stream as std::string */
std::string PNGDecoder::get_chunk_name(std::ifstream& image_stream) {
    std::string name(4, '\0');
    image_stream.read(&name.front(), 4);
    return name;
}

std::string PNGDecoder::get_last_edited() {
    return this->last_edited.toString().toStdString();
}

const std::vector<std::string>& PNGDecoder::get_text() {
    return this->text;
}

unsigned int PNGDecoder::get_width() {
    return this->img_width;
}

unsigned int PNGDecoder::get_height() {
    return this->img_height;
}

std::string PNGDecoder::get_appended_data() {
    return this->appended_data;
}

void PNGDecoder::reset() {
    this->img_width = 0;
    this->img_height = 0;
    this->img_bit_depth = 0;
    this->img_color_type = 0;
    this->img_compression_method = 0;
    this->img_filter_method = 0;
    this->img_interlace_method = 0;
    this->last_edited.setDate(QDate(0, 0, 0));
    this->last_edited.setTime(QTime(0, 0, 0));
    this->text.clear();
    this->appended_data = "";
}