
#include "output/I18nManager.hpp"

I18nManager::I18nManager(const std::string &lang)
: language_(lang)
{
    std::string filename = "locales/" + lang + ".json";

    JSONManager jsonManager(filename);
    if (!jsonManager.load(messagesData_))
    {
        std::cerr << "⚠️ Failed to load language file : " << filename << std::endl;
    }
}

std::string I18nManager::getText(const std::string &key) const 
{
    std::string res;
    if (messagesData_.contains(key))
    {
        res = messagesData_[key];
    }else if (language_ == "ja")
    {
        res = "* [" + key + "] 未定義";
    }else
    {
        res = "* [" + key + "] Undefined";
    }
    return res;
}


