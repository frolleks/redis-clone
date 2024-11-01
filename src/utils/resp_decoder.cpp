#include "resp_decoder.h"
#include <sstream>
#include <stdexcept>

// Parses a single RESP bulk string
std::string RespDecoder::parse_bulk_string(const std::string &input) {
    std::istringstream iss(input);

    // Check for the bulk string marker '$'
    char bulkMarker;
    iss >> bulkMarker;
    if (bulkMarker != '$') {
        throw std::runtime_error(
            "Invalid RESP format: Expected '$' for bulk string");
    }

    // Read the length of the bulk string
    int bulkLength;
    iss >> bulkLength;
    iss.ignore(2); // Ignore the following \r\n

    // Special case for NULL bulk strings (encoded as `$-1\r\n`)
    if (bulkLength == -1) {
        return ""; // Return an empty string or handle as NULL based on your
                   // application logic
    }

    // Read the actual bulk string data
    std::string result(bulkLength, '\0');
    iss.read(&result[0], bulkLength);
    iss.ignore(2); // Ignore the following \r\n

    return result;
}

// Parses a RESP-encoded array and returns a vector of strings
std::vector<std::string>
RespDecoder::parse_resp_array(const std::string &input) {
    std::istringstream iss(input);
    std::vector<std::string> result;

    // Ensure the input starts with '*', indicating an array
    char arrayMarker;
    iss >> arrayMarker;
    if (arrayMarker != '*') {
        throw std::runtime_error("Invalid RESP format: Expected '*'");
    }

    // Read the array length
    int arrayLength;
    iss >> arrayLength;
    iss.ignore(2); // Ignore the following \r\n

    // Parse each bulk string in the array
    for (int i = 0; i < arrayLength; ++i) {
        char bulkMarker;
        iss >> bulkMarker;
        if (bulkMarker != '$') {
            throw std::runtime_error("Invalid RESP format: Expected '$'");
        }

        int bulkLength;
        iss >> bulkLength;
        iss.ignore(2); // Ignore the following \r\n

        std::string element(bulkLength, '\0');
        iss.read(&element[0], bulkLength);
        iss.ignore(2); // Ignore the following \r\n

        result.push_back(element);
    }

    return result;
}
