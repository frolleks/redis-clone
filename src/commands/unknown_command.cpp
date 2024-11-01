#include "unknown_command.h"

UnknownCommand::UnknownCommand(const std::string &cmd) : cmd_(cmd) {}

std::string UnknownCommand::execute(Store & /*store*/) {
    return encoder.error("ERROR: Unknown command '" + cmd_ + "'");
}