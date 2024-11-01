#include "ping.h"

PingCommand::PingCommand(const std::vector<std::string> &args) {}

std::string PingCommand::execute(Store & /*store*/) {
    return encoder.simple_string("PONG");
}