#include "info.h"
#include "../utils/gen_info_string.h"

InfoCommand::InfoCommand(const std::vector<std::string> &args) {}

std::string InfoCommand::execute(Store & /*store*/) {
    std::string info = gen_info_string();
    return encoder.bulk_string(info);
}