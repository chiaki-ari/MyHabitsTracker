#ifndef I18N_MANAGER_HPP
#define I18N_MANAGER_HPP

#include "model/JSONManager.hpp"
#include "output/I18nInterface.hpp"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

class I18nManager : public I18nInterface
{
public:
    I18nManager(const std::string &lang);
    
    std::string getText(const std::string &key) const override;

private:
    json messagesData_;
    std::string language_;
};

#endif // I18N_MANAGER_HPP