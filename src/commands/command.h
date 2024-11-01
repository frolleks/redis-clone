#ifndef COMMAND_H
#define COMMAND_H

#include "../store.h"
#include <string>

class Command {
  public:
    virtual ~Command() {}
    virtual std::string execute(Store &store) = 0;
};

#endif // COMMAND_H