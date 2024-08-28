
#include <optional>
#include <string>
#include <span>

#include "../framework.h"
#include "sigscanner.hpp"

namespace buz::mem {
    inline constexpr bool inRange(char x, char a, char b) {
        return x >= a && x <= b;
    }

    inline constexpr uint8_t getBits(char x) {
        return inRange(x & (~0x20), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA)
            : (inRange(x, '0', '9') ? x - '0' : 0);
    }

    inline constexpr uint8_t getByte(std::span<const char> sig) {
        return (getBits(sig[0]) << 4) | getBits(sig[1]);
    }

    uintptr_t scan_for_sig(const std::string& sig) {
        const char* sigData = sig.data();
        uintptr_t firstMatch = 0;

        static const auto rangeStart = reinterpret_cast<uintptr_t>(GetModuleHandleA("bedrock_server.exe"));
        static MODULEINFO moduleInfo;
        static bool initialized = false;

        if (!initialized) {
            initialized = true;
            GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(rangeStart), &moduleInfo, sizeof(MODULEINFO));
        }
        static const uintptr_t rangeEnd = rangeStart + moduleInfo.SizeOfImage;

        uint8_t patternByte = getByte({ sigData, 2 });
        const char* oldPattern = sigData;

        for (uintptr_t current = rangeStart; current < rangeEnd; ++current) {
            if (!*sigData) return firstMatch;

            while (*sigData == ' ') ++sigData;

            if (!*sigData) return firstMatch;

            if (oldPattern != sigData) {
                oldPattern = sigData;
                if (*sigData != '?') patternByte = getByte({ sigData, 2 });
            }

            if (*sigData == '?' || *reinterpret_cast<uint8_t*>(current) == patternByte) {
                if (!firstMatch) firstMatch = current;

                if (!sigData[2] || !sigData[1]) return firstMatch;

                sigData += 2;
            }
            else {
                sigData = sig.data();
                firstMatch = 0;
            }
        }
        return 0;
    }

    uintptr_t get_offset_from_call(const std::string& sig) {
        uintptr_t callRef = scan_for_sig(sig);
        if (!callRef)
            return 0;

        auto* offsetPtr = reinterpret_cast<int32_t*>(callRef + 1);
        int32_t offset = *offsetPtr;
        uintptr_t finalAddr = callRef + 5 + offset;

        return finalAddr;
    }
}