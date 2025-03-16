#ifndef OUTPUT_INTERFACE_HPP
#define OUTPUT_INTERFACE_HPP

#include <string>

class OutputInterface {
public:
    virtual void print(const std::string& message, bool newline = true) = 0;
    virtual ~OutputInterface() = default;
};

#endif // OUTPUT_INTERFACE_HPP
