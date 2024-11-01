#ifndef UNKNOWN_COMMAND_H
#define UNKNOWN_COMMAND_H

#include "../utils/resp_encoder.h"
#include "command.h"
#include <string>

class UnknownCommand : public Command {
  public:
    explicit UnknownCommand(const std::string &cmd);
    std::string execute(Store &store) override;

  private:
    RespEncoder encoder;
    std::string cmd_;
};

#endif // UNKNOWN_COMMAND_H