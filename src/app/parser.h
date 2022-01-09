#pragma once
#include <filesystem>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace app {

/* Class responsible for input argument parsing. */
class Parser {
public:
    /* Typedefs for convenience. */

    using Path = std::filesystem::path;
    using Args = std::vector<std::string>;
    using Result = std::tuple<Path, Path, bool>;

    /* Create an instance of the parser by passing the commandline arguments. */
    Parser(int argc, const char* argv[]);

    /* Returns an explanatory string about how to use the program. */
    static std::string Usage();

    /* Returns the parsed arguments as a tuple. */
    Result Arguments() const;
private:
    Args FilterVerbose(Args args);
    bool useLogging;
    Path rom;
    Path ram;
};

/* Custom exception for argument parser errors. */
class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& what);
};

}
