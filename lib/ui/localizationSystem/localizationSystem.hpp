#pragma once

#include <vector>
#include <map>
#include <string>
#include <exception>

namespace ui {

    class LocalizationNonexistentKeyException : public std::exception{
    protected:
        std::string str;
        std::string nowLanguage;
        std::string defaultLanguage;
        std::string key;

    public:
        LocalizationNonexistentKeyException(std::string nowLanguage, std::string defaultLanguage, std::string key);
        const char* what() const noexcept override;
    };

    class LocalizationSystem {
    protected:
        static std::map<std::string, std::map<std::string, std::u32string>> text;
        static std::string strNowLanguage;
        static std::map<std::string, std::u32string>* nowLanguage;
        static std::string strDefaultLanguage;
        static std::map<std::string, std::u32string>* defaultLanguage;

    public:
        static void loadFromDirectory(std::string path);

        static void setNowLanguage(std::string language);
        static void setDefaultLanguage(std::string language);

        static std::u32string getText(std::string key);
        static std::u32string getText(std::string language, std::string key);

        static std::vector<std::string> getLanguages();
    };
} // ui