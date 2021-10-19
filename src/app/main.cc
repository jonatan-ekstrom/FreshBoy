#include <cstdlib>
#include <exception>
#include <iostream>
#include "app.h"

int main(const int argc, const char* argv[]) {
    int exitCode{EXIT_FAILURE};
    if (argc < 2 || argc > 3) return exitCode;
    try {
        auto emulator{app::Emulator_::Create()};
        emulator->Run(argv[1], argc == 3 ? argv[2] : "");
        exitCode = EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
