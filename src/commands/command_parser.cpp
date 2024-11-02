#include "command_parser.h"
#include "../utils/resp_decoder.h"
#include "del.h"
#include "echo.h"
#include "get.h"
#include "info.h"
#include "ping.h"
#include "set.h"
#include "unknown_command.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

CommandParser::CommandParser() {
    command_map_["SET"] = [](const std::vector<std::string> &args) {
        return std::make_unique<SetCommand>(args);
    };
    command_map_["GET"] = [](const std::vector<std::string> &args) {
        return std::make_unique<GetCommand>(args);
    };
    command_map_["DEL"] = [](const std::vector<std::string> &args) {
        return std::make_unique<DelCommand>(args);
    };
    command_map_["PING"] = [](const std::vector<std::string> &args) {
        return std::make_unique<PingCommand>(args);
    };
    command_map_["ECHO"] = [](const std::vector<std::string> &args) {
        return std::make_unique<EchoCommand>(args);
    };
    command_map_["INFO"] = [](const std::vector<std::string> &args) {
        return std::make_unique<InfoCommand>(args);
    };
}

std::unique_ptr<Command> CommandParser::parse(const std::string &commandStr) {
    std::vector<std::string> args;

    // Use RespDecoder to parse the RESP input
    try {
        args = RespDecoder::parse_resp_array(commandStr);
    } catch (const std::runtime_error &e) {
        return std::make_unique<UnknownCommand>(e.what());
    }

    // The first argument is the command
    if (args.empty()) {
        return std::make_unique<UnknownCommand>("Empty command");
    }

    // Convert the command to uppercase for case-insensitive matching
    std::string cmd = args[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    // Remove the command from args
    args.erase(args.begin());

    auto it = command_map_.find(cmd);
    if (it != command_map_.end()) {
        // Command found, call the associated lambda to create the command
        // object
        return it->second(args);
    } else {
        // Command not found, return UnknownCommand
        return std::make_unique<UnknownCommand>(cmd);
    }
}
