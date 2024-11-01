#ifndef SET_H
#define SET_H

#include "../store.h"
#include "command.h"
#include <string>
#include <vector>

class SetCommand : public Command {
  public:
    explicit SetCommand(const std::vector<std::string> &args);
    std::string execute(Store &store) override;

  private:
    std::string key_;
    std::string value_;
    bool valid_;
    std::string error_message_;

    void parseArguments(const std::vector<std::string> &args);
};

#endif // SET_H