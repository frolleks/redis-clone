#ifndef GET_H
#define GET_H

#include "../store.h"
#include "../utils/resp_encoder.h"
#include "command.h"
#include <string>
#include <vector>

class GetCommand : public Command {
  public:
    explicit GetCommand(const std::vector<std::string> &args);
    std::string execute(Store &store) override;

  private:
    RespEncoder encoder;
    std::string key_;
    bool valid_;
    std::string error_message_;

    void parseArguments(const std::vector<std::string> &args);
};

#endif // GET_H