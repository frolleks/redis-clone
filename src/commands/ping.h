#ifndef PING_H
#define PING_H

#include "command.h"
#include <string>

class PingCommand : public Command {
  public:
    explicit PingCommand(const std::vector<std::string> &args);
    std::string execute(Store &store) override;
};

#endif // PING_H