#include <cstdlib>
#include <exception>
#include <iostream>
#include "app.h"

int main(const int argc, const char *const *const argv) {
    int exitCode{EXIT_FAILURE};
    if (argc != 2) return exitCode;
    try {
        app::Emulator emulator;
        emulator.Run(argv[1]);
        exitCode = EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
