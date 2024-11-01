#ifndef DEL_H
#define DEL_H

#include "../store.h"
#include "command.h"
#include <string>
#include <vector>

class DelCommand : public Command {
  public:
    explicit DelCommand(const std::vector<std::string> &args);
    std::string execute(Store &store) override;

  private:
    std::string key_;
    bool valid_;
    std::string error_message_;

    void parseArguments(const std::vector<std::string> &args);
};

#endif // DEL_H