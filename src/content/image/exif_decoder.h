#pragma once

#include <vector>
#include <string>
#include <sstream>

/* TODO! */
class ExifDecoder {
    private:
        std::vector<std::string> values;
    public:
        ExifDecoder();
        void decode(std::stringstream& data);
};