#ifndef ECHO_H
#define ECHO_H

#include "../utils/resp_encoder.h"
#include "command.h"
#include <string>
#include <vector>

class EchoCommand : public Command {
  public:
    explicit EchoCommand(const std::vector<std::string> &args);
    std::string execute(Store & /*store*/) override;

  private:
    RespEncoder encoder;

    std::string value_;
    bool valid_;
    std::string error_message_;

    void parseArguments(const std::vector<std::string> &args);
};

#endif // ECHO_H