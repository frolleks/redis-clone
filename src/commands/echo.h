#ifndef ECHO_H
#define ECHO_H

#include "command.h"
#include <string>
#include <vector>

class EchoCommand : public Command {
  public:
    explicit EchoCommand(const std::vector<std::string> &args);
    std::string execute(Store & /*store*/) override;

  private:
    std::string value_;
    bool valid_;
    std::string error_message_;

    void parseArguments(const std::vector<std::string> &args);
};

#endif // ECHO_H