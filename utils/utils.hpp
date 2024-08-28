#pragma once

#include <string>

namespace buz::utils {
	std::string to_big_int(uint32_t value);
	std::string to_base64(const std::vector<uint8_t>& data);
	void		hexdump(const std::string& data);
	std::string format_kilo(size_t number);
}