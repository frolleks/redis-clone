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

    // Match the command and create the appropriate Command object
    if (cmd == "SET") {
        return std::make_unique<SetCommand>(args);
    } else if (cmd == "GET") {
        return std::make_unique<GetCommand>(args);
    } else if (cmd == "DEL") {
        return std::make_unique<DelCommand>(args);
    } else if (cmd == "PING") {
        return std::make_unique<PingCommand>(args);
    } else if (cmd == "ECHO") {
        return std::make_unique<EchoCommand>(args);
    } else if (cmd == "INFO") {
        return std::make_unique<InfoCommand>(args);
    } else {
        return std::make_unique<UnknownCommand>(cmd);
    }
}
