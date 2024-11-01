#include "command_parser.h"
#include "del.h"
#include "echo.h"
#include "get.h"
#include "ping.h"
#include "set.h"
#include "unknown_command.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

std::unique_ptr<Command> CommandParser::parse(const std::string &commandStr) {
    std::istringstream iss(commandStr);
    std::string cmd;
    iss >> cmd;

    // Convert command to uppercase to ensure case-insensitive matching
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    // Read the rest of the input as raw arguments
    std::string restOfLine;
    std::getline(iss, restOfLine);

    // Trim leading whitespace
    restOfLine.erase(
        restOfLine.begin(),
        std::find_if(restOfLine.begin(), restOfLine.end(),
                     [](unsigned char ch) { return !std::isspace(ch); }));

    // Split restOfLine into tokens
    std::vector<std::string> args;
    std::istringstream argsStream(restOfLine);
    std::string arg;
    while (argsStream >> arg) {
        args.push_back(arg);
    }

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
    } else {
        return std::make_unique<UnknownCommand>(cmd);
    }
}