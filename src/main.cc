#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    int exitCode{EXIT_FAILURE};
    try {
        std::cout << "Hello World!" << std::endl;
        exitCode = EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
