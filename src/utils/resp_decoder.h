#ifndef RESP_DECODER_H
#define RESP_DECODER_H

#include <string>
#include <vector>

class RespDecoder {
  public:
    // Parses a single RESP bulk string and returns it as a string
    // Throws an exception if the input is not a valid bulk string
    static std::string parse_bulk_string(const std::string &input);

    // Parses a RESP-encoded array and returns a vector of parsed elements
    // Throws an exception if the input is not valid RESP format
    static std::vector<std::string> parse_resp_array(const std::string &input);
};

#endif // RESP_DECODER_H
