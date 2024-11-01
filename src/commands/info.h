#ifndef INFO_COMMAND_H
#define INFO_COMMAND_H

#include "../utils/resp_encoder.h"
#include "command.h"
#include <string>

class InfoCommand : public Command {
  public:
    explicit InfoCommand(const std::vector<std::string> &args);
    std::string execute(Store & /*store*/) override;

  private:
    RespEncoder encoder;
};

#endif // INFO_COMMAND_H
