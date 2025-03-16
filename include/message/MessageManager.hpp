#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include "message/MessageInterface.hpp"
#include "json.hpp"

using json = nlohmann::json;

class MessageManager : public MessageInterface {
    public:
        MessageManager(const std::string& lang);
        std::string getMessage(const std::string& key) const override;
    
    private:
        json messagesData_;
        std::string language_;
    };

#endif // MESSAGE_MANAGER_HPP