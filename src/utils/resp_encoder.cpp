#include "resp_encoder.h"
#include <sstream>

// Converts a string to a RESP bulk string
std::string RespEncoder::bulk_string(const std::string &input) const {
    std::ostringstream resp;
    resp << "$" << input.size() << "\r\n" << input << "\r\n";
    return resp.str();
}

// Converts a string to a RESP simple string
std::string RespEncoder::simple_string(const std::string &input) const {
    return "+" + input + "\r\n";
}

// Converts an integer to a RESP integer type
std::string RespEncoder::integer(int number) const {
    return ":" + std::to_string(number) + "\r\n";
}

// Converts a vector of strings to a RESP array
std::string RespEncoder::array(const std::vector<std::string> &elements) const {
    std::ostringstream resp;
    resp << "*" << elements.size() << "\r\n";
    for (const auto &element : elements) {
        resp << bulk_string(element);
    }
    return resp.str();
}

// Converts an error message to a RESP error type
std::string RespEncoder::error(const std::string &message) const {
    return "-" + message + "\r\n";
}
