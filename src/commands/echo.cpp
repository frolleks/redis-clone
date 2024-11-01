#include "echo.h"
#include <sstream>

EchoCommand::EchoCommand(const std::vector<std::string> &args) : valid_(false) {
    parseArguments(args);
}

void EchoCommand::parseArguments(const std::vector<std::string> &args) {
    if (args.empty()) {
        valid_ = false;
        error_message_ =
            encoder.error("ERROR: ECHO command requires at least one argument");
        return;
    }

    // Concatenate all arguments into a single string
    std::string valueStr;
    for (const auto &arg : args) {
        if (!valueStr.empty()) {
            valueStr += " "; // Add space between words
        }
        valueStr += arg;
    }

    // Handle quoted strings in value
    if (!valueStr.empty() && valueStr.front() == '"' &&
        valueStr.back() == '"') {
        // Remove the opening and closing quotes
        value_ = valueStr.substr(1, valueStr.size() - 2);
    } else if (!valueStr.empty() &&
               (valueStr.front() == '"' || valueStr.back() == '"')) {
        // If only one quote is found, it's an error
        valid_ = false;
        error_message_ = encoder.error("ERROR: Missing closing quote in value");
        return;
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

    return encoder.bulk_string(value_);
}