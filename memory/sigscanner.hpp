#pragma once

#include <cstdint>

namespace buz::mem {
	uintptr_t	scan_for_sig(const std::string& sig);
	uintptr_t	get_offset_from_call(const std::string& sig);
}