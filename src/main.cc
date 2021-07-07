#include <cstdlib>
#include <exception>
#include <iostream>
#include "demo.h"

int main() {
    int exitCode{EXIT_FAILURE};
    try {
        gb::Demo demo;
        demo.Run();
        exitCode = EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
