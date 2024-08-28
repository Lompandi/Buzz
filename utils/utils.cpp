
#include <array>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <format>

#include "utils.hpp"

namespace buz::utils {
    std::string to_big_int(uint32_t value) {
        std::array<char, 4> bytes;

        bytes[0] = static_cast<char>((value >> 24) & 0xFF); 
        bytes[1] = static_cast<char>((value >> 16) & 0xFF);
        bytes[2] = static_cast<char>((value >> 8) & 0xFF);
        bytes[3] = static_cast<char>(value & 0xFF); 

        return std::string(bytes.data(), bytes.size());
    }

    const std::array<char, 64> base64_table = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
    };

    std::string to_base64(const std::vector<uint8_t>& data) {
        std::string encoded;
        encoded.reserve((data.size() + 2) / 3 * 4); 

        size_t i = 0;
        while (i < data.size()) {
            uint32_t value = (data[i] << 16) | (i + 1 < data.size() ? data[i + 1] << 8 : 0) | (i + 2 < data.size() ? data[i + 2] : 0);

            encoded.push_back(base64_table[(value >> 18) & 0x3F]);
            encoded.push_back(base64_table[(value >> 12) & 0x3F]);
            encoded.push_back(i + 1 < data.size() ? base64_table[(value >> 6) & 0x3F] : '=');
            encoded.push_back(i + 2 < data.size() ? base64_table[value & 0x3F] : '=');

            i += 3;
        }

        return encoded;
    }

    void hexdump(const std::string& data) {
        constexpr size_t addressWidth = 8;
        constexpr size_t bytesPerLine = 16;

        for (size_t i = 0; i < data.size(); i += bytesPerLine) {
            std::cout << std::format("{:0{}} ", i, addressWidth * 2);
            for (size_t j = 0; j < bytesPerLine; ++j) {
                if (i + j < data.size()) {
                    std::cout << std::format("{:02x} ", static_cast<unsigned char>(data[i + j]));
                }
                else {
                    std::cout << "   ";
                }
            }

            std::cout << " |";
            for (size_t j = 0; j < bytesPerLine; ++j) {
                if (i + j < data.size()) {
                    std::cout << (std::isprint(static_cast<unsigned char>(data[i + j]))
                        ? data[i + j] : '.');
                }
                else 
                    std::cout << ' ';
            }
            std::cout << '|' << std::endl;
        }
    }

    std::string format_kilo(size_t number) {
        if (number < 1000) 
            return std::format("{}", number);

        double inThousands = number / 1000.0;
        return std::format("{:.1f}k", std::floor(inThousands * 10 + 0.5) / 10);
    }
}