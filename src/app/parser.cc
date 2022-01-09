#include "parser.h"

using namespace app;

namespace {

constexpr auto Invalid{"Parser - Invalid number of arguments."};

void CheckSize(const Parser::Args& args) {
    const auto size{args.size()};
    const auto ok{size == 1 || size == 2};
    if (!ok) {
        throw ParseError{Invalid};
    }
}

void CheckExists(const std::string& str) {
    Parser::Path path;
    try {
        path = str;
    } catch (...) {
        throw ParseError{"Parser - Path: " + str + " is not valid."};
    }
    if (!is_regular_file(path)) {
        throw ParseError{"Parser - Path: " + path.string() + " does not refer to a file."};
    }
}

}

namespace app {

Parser::Parser(const int argc, const char* argv[])
    : useLogging{false} {
    if (argc == 1) {
        throw ParseError{Invalid};
    }
    const Args args{&argv[1], &argv[1] + (argc - 1)};

    // Check if we're using logging.
    const auto filtered{FilterVerbose(args)};

    // Verify the size of the filtered argument list.
    CheckSize(filtered);

    // Extract ROM path.
    const auto a1{filtered[0]};
    CheckExists(a1);
    this->rom = a1;

    if (filtered.size() != 2) return;

    // Extract RAM path.
    const auto a2{filtered[1]};
    CheckExists(a2);
    this->ram = a2;
}

Parser::Args Parser::FilterVerbose(Args args) {
    constexpr auto verbose{"-v"};
    for (auto iter{args.begin()}; iter != args.end(); ++iter) {
        if (*iter == verbose) {
            args.erase(iter);
            this->useLogging = true;
            break;
        }
    }
    return args;
}

std::string Parser::Usage() {
    return "Usage: FreshBoy [-v] <ROM path> [RAM path]";
}

Parser::Result Parser::Arguments() const {
    return { this->rom, this->ram, this->useLogging };
}

ParseError::ParseError(const std::string& what)
    : std::runtime_error{what} {}

}
