#ifndef MESSAGE_INTERFACE_HPP
#define MESSAGE_INTERFACE_HPP

#include <string>

class MessageInterface {
    public:
        virtual std::string getMessage(const std::string& key) const = 0;
        virtual ~MessageInterface() = default;
    };
    
#endif // MESSAGE_INTERFACE_HPP