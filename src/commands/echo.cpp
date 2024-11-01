#include "echo.h"
#include <sstream>

EchoCommand::EchoCommand(const std::vector<std::string> &args) : valid_(false) {
    parseArguments(args);
}

void EchoCommand::parseArguments(const std::vector<std::string> &args) {
    if (args.size() < 1) {
        valid_ = false;
        error_message_ =
            "-ERROR: ECHO command requires at least one argument\r\n";
        return;
    }

    std::string valueStr;
    valueStr = args[0];

    // Handle quoted strings in value
    if (!valueStr.empty() && valueStr.front() == '"') {
        std::istringstream valueStream(valueStr);
        std::getline(valueStream, value_, '"'); // Skip the opening quote
        std::getline(valueStream, value_, '"'); // Read until the closing quote

        // If closing quote is not found
        if (valueStream.fail()) {
            valid_ = false;
            error_message_ = "-ERROR: Missing closing quote in value\r\n";
            return;
        }
    } else {
        // Value is unquoted
        value_ = valueStr;
    }

    valid_ = true;
}

std::string EchoCommand::execute(Store & /*store*/) {
    if (!valid_) {
        return error_message_;
    }

    return "\"" + value_ + "\"\r\n";
}