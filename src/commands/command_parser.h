#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "command.h"
#include <memory>
#include <string>
#include <vector>

class CommandParser {
  public:
    std::unique_ptr<Command> parse(const std::string &commandStr);
};

#endif // COMMAND_PARSER_H