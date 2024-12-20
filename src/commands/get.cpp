#include "get.h"

GetCommand::GetCommand(const std::vector<std::string> &args) : valid_(false) {
    parseArguments(args);
}

void GetCommand::parseArguments(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        valid_ = false;
        error_message_ =
            encoder.error("ERROR: GET command requires exactly one key");
        return;
    }
    key_ = args[0];
    valid_ = true;
}

std::string GetCommand::execute(Store &store) {
    if (!valid_) {
        return error_message_;
    }
    std::string value = store.get(key_);
    if (!value.empty()) {
        return encoder.bulk_string(value);
    }
    return "-ERROR: Key not found\r\n";
}