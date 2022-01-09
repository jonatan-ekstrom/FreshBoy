#include <cstdlib>
#include <exception>
#include <iostream>
#include "app.h"
#include "parser.h"

using namespace app;

int main(const int argc, const char* argv[]) {
    int exitCode{EXIT_FAILURE};
    try {
        const Parser parser{argc, argv};
        const auto [rom, ram, log] = parser.Arguments();
        auto emulator{Emulator_::Create()};
        emulator->Run(rom, ram, log);
        exitCode = EXIT_SUCCESS;
    } catch (const ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << Parser::Usage() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return exitCode;
}
