#ifndef RESP_ENCODER_H
#define RESP_ENCODER_H

#include <string>
#include <vector>

class RespEncoder {
  public:
    // Converts a string to a RESP bulk string
    std::string bulk_string(const std::string &input) const;

    // Converts a string to a RESP simple string
    std::string simple_string(const std::string &input) const;

    // Converts an integer to a RESP integer type
    std::string integer(int number) const;

    // Converts a vector of strings to a RESP array
    std::string array(const std::vector<std::string> &elements) const;

    // Converts an error message to a RESP error type
    std::string error(const std::string &message) const;
};

#endif // RESP_ENCODER_H
