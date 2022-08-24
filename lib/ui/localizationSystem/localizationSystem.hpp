#pragma once

#include <vector>
#include <map>
#include <string>

namespace ui {

    class LocalizationSystem {
    protected:
        static std::map<std::string, std::map<std::string, std::u32string>> text;
        static std::map<std::string, std::u32string>* nowLanguage;

    public:
        static void loadFromDirectory(std::string path);

        static void setNowLanguage(std::string nowLanguage);

        static std::u32string getText(std::string key);
        static std::u32string getText(std::string language, std::string key);

        static std::vector<std::string> getLanguages();
    };

} // ui