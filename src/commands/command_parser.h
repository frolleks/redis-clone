#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "command.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class CommandParser {
  public:
    CommandParser();
    std::unique_ptr<Command> parse(const std::string &commandStr);

  private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Command>(
                                        const std::vector<std::string> &)>>
        command_map_;
};

#endif // COMMAND_PARSER_H