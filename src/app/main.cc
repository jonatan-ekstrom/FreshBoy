#include <cstdlib>
#include <exception>
#include <iostream>
#include "app.h"

int main() {
    int exitCode{EXIT_FAILURE};
    try {
        app::Emulator emulator;
        emulator.Run("/home/jonatan/Desktop/zelda.gb");
        exitCode = EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
