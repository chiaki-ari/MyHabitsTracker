#ifndef INPUT_INTERFACE_HPP
#define INPUT_INTERFACE_HPP

#include <optional>
#include <string>

class InputInterface {
public:
    virtual std::optional<std::string> getStringInput() = 0;
    virtual ~InputInterface() = default;
};

#endif // INPUT_INTERFACE_HPP
