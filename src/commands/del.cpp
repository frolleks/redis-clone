#include "del.h"

DelCommand::DelCommand(const std::vector<std::string> &args) : valid_(false) {
    parseArguments(args);
}

void DelCommand::parseArguments(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        valid_ = false;
        error_message_ = "-ERROR: DEL command requires exactly one key\r\n";
        return;
    }
    key_ = args[0];
    valid_ = true;
}

std::string DelCommand::execute(Store &store) {
    if (!valid_) {
        return error_message_;
    }
    store.del(key_);
    return "+OK\r\n";
}