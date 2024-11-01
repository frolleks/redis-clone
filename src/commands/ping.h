#ifndef PING_H
#define PING_H

#include "../utils/resp_encoder.h"
#include "command.h"
#include <string>
#include <vector>

class PingCommand : public Command {
  public:
    explicit PingCommand(const std::vector<std::string> &args);
    std::string execute(Store &store) override;

  private:
    RespEncoder encoder;
};

#endif // PING_H