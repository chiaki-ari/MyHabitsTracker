#ifndef I18N_INTERFACE_HPP
#define I18N_INTERFACE_HPP

#include <string>

class I18nInterface
{
public:
    virtual std::string getText(const std::string &key) const = 0;
    virtual ~I18nInterface() = default;
};

#endif // I18N_INTERFACE_HPP