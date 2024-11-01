#include "set.h"
#include <sstream>

SetCommand::SetCommand(const std::vector<std::string> &args) : valid_(false) {
    parseArguments(args);
}

void SetCommand::parseArguments(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        valid_ = false;
        error_message_ =
            encoder.error("ERROR: SET command requires a key and a value");
        return;
    }

    key_ = args[0];

    // Reconstruct the value from the remaining arguments
    std::string valueStr;
    for (size_t i = 1; i < args.size(); ++i) {
        if (i > 1) {
            valueStr += ' ';
        }
        valueStr += args[i];
    }

    // Handle quoted strings in value
    if (!valueStr.empty() && valueStr.front() == '"') {
        std::istringstream valueStream(valueStr);
        std::getline(valueStream, value_, '"'); // Skip the opening quote
        std::getline(valueStream, value_, '"'); // Read until the closing quote

        // If closing quote is not found
        if (valueStream.fail()) {
            valid_ = false;
            error_message_ =
                encoder.error("ERROR: Missing closing quote in value");
            return;
        }
    } else {
        // Value is unquoted
        value_ = valueStr;
    }

    valid_ = true;
}

std::string SetCommand::execute(Store &store) {
    if (!valid_) {
        return error_message_;
    }
    store.set(key_, value_);
    return encoder.simple_string("OK");
}