#include "localizationSystem.hpp"

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>

typedef unsigned uint;

namespace ui {
    bool findNotSpace(const char32_t &a) {
        bool r = a != U' ' && a != U'\n' && a != U'\t' && a != U':';
        return r;
    }

    bool findSpace(const char32_t &a) {
        return a == U' ' || a == U'\n' || a == U'\t' || a == U':';
    }

    bool findQuoteMarks(const char32_t &a){
        return a == U'"';
    }

    std::u32string::iterator searchQuoteMark(std::u32string::iterator first, std::u32string::iterator last){
        std::u32string::iterator result;
        while ((result = std::find_if(first, last, findQuoteMarks)) != last && *(result - 1) == U'\\');
        return result;
    }

    LocalizationNonexistentKeyException::LocalizationNonexistentKeyException(std::string nowLanguage, std::string defaultLanguage, std::string key) :
        nowLanguage(nowLanguage), defaultLanguage(defaultLanguage), key(key),
        str(std::string{"could not find the key '"} + key + std::string{"' in either the specified language '"} + nowLanguage + std::string{"' or the standard '"} + defaultLanguage + std::string{"'"}){}

    const char *LocalizationNonexistentKeyException::what() const noexcept {
        return str.c_str();
    }

    std::map<std::string, std::map<std::string, std::u32string>> LocalizationSystem::text{};
    std::string LocalizationSystem::strNowLanguage;
    std::map<std::string, std::u32string>* LocalizationSystem::nowLanguage{nullptr};
    std::string LocalizationSystem::strDefaultLanguage;
    std::map<std::string, std::u32string>* LocalizationSystem::defaultLanguage{nullptr};

    void LocalizationSystem::loadFromDirectory(std::string path) {

        std::u32string files{};

        {
            std::u32string str{};
            for (auto &languageFile: std::filesystem::directory_iterator(path)) {
                if (languageFile.path().extension() == ".loc") {
                    std::basic_ifstream<char32_t> fin(languageFile.path());
                    std::getline(fin, str, U'\0');
                    files += str + U'\n';
                }
            }
        }

        std::string key;

        std::u32string::iterator cursor = files.begin();
        while ((cursor = std::find_if(cursor, files.end(), findNotSpace)) != files.end()){
            if (*cursor == U'"'){
                std::u32string::iterator endText{searchQuoteMark(cursor + 1, files.end())};
                (*nowLanguage)[key] = {cursor + 1, endText};
                cursor = endText + 1;
            } else{
                std::u32string::iterator endName{std::find_if(cursor, files.end(), findSpace)};
                if (*cursor == U'-'){
                    nowLanguage = &text[{cursor + 1, endName}];
                } else{
                    key = {cursor, endName};
                }
                cursor = endName;
            }
        }
    }

    void LocalizationSystem::setNowLanguage(std::string language) {
        strNowLanguage = language;
        nowLanguage = &text[language];
    }

    void LocalizationSystem::setDefaultLanguage(std::string language) {
        strDefaultLanguage = language;
        defaultLanguage = &text[language];
    }

    std::u32string LocalizationSystem::getText(std::string key) {
        if (nowLanguage && nowLanguage->find(key) != nowLanguage->end())
            return (*nowLanguage)[key];
        else if (defaultLanguage && defaultLanguage->find(key) != defaultLanguage->end())
            return (*defaultLanguage)[key];
        else
            throw LocalizationNonexistentKeyException{strNowLanguage, strDefaultLanguage, key};
    }

    std::u32string LocalizationSystem::getText(std::string language, std::string key) {
        return LocalizationSystem::text[language][key];
    }

    std::vector<std::string> LocalizationSystem::getLanguages() {
        std::vector<std::string> result{};

        for (auto & pair : text) {
            result.push_back(pair.first);
        }

        return result;
    }
}