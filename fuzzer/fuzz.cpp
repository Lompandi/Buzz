
#include <windows.h>
#include <iostream>
#include <random>
#include <chrono>


#include "fuzz.hpp"
#include "../utils/utils.hpp"
#include "../logger/console.hpp"
#include "../packets/streams.hpp"
#include "../memory/sigscanner.hpp"


namespace buz {

    std::string g_fuzz_packet;

    using login_packet_ctor_t = int64_t(__fastcall*)(void*);
    using login_packet_read_t = int64_t(__fastcall*)(void*, void*, ReadOnlyBinaryStream&);
    using rdonly_binstream_ctor_t = int64_t(__fastcall*)(void*, const std::string&, bool);

    std::string gen_fuzz_input() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> lengthDist(40, 3192);
        std::uniform_int_distribution<int> byteDist(0, 255);

        size_t length = static_cast<size_t>(lengthDist(mt));

        std::vector<char> randomBytes(length);
        std::generate(randomBytes.begin(), randomBytes.end(), [&]() {
            return static_cast<char>(byteDist(mt));
        });

        return std::string(randomBytes.begin(), randomBytes.end());
    }

    LONG WINAPI UnhandledExceptionFilter(EXCEPTION_POINTERS* exceptionInfo) {
        std::cout << "Unhandled exception caught!\n";
        std::cout << "Exception code: 0x" << std::hex << exceptionInfo->ExceptionRecord->ExceptionCode << std::endl;

        std::cout << "Last fuzz packet:\n";
        utils::hexdump(g_fuzz_packet);

        return EXCEPTION_CONTINUE_SEARCH;
    }

    // Start fuzzing
    void start_fuzzing() {
        setup_console();
        print_banner();

        SetUnhandledExceptionFilter(UnhandledExceptionFilter);

        size_t counter = 0;

        auto start = std::chrono::steady_clock::now();
        auto last_print = start;

        std::string version = utils::to_big_int(686);

        std::cout << "¢~¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢¡\n";
        std::cout << "¢x input tested " << utils::format_kilo(counter) << "\t\t\t¢x\n";
        std::cout << "¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t\n";
        std::cout << "¢x created by consolebreak               ¢x\n";
        std::cout << "¢¢¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢£\n";

        /* Main fuzzing loop will be here , waiting to add...*/

        return;
    }
}