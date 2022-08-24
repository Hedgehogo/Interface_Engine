#include "localizationSystem.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>

typedef unsigned uint;

namespace ui {
    std::map<std::string, std::map<std::string, std::u32string>> LocalizationSystem::text{};
    std::map<std::string, std::u32string>* LocalizationSystem::nowLanguage{NULL};

    void LocalizationSystem::loadFromDirectory(std::string path) {

        std::u32string files{};

        std::u32string str{};
        for (auto& languageFile : std::filesystem::directory_iterator(path)) {
            if (languageFile.path().extension() == ".loc") {
                std::basic_ifstream<char32_t> fin(languageFile.path());
                std::getline(fin, str, U'\0');
                files += str + U'\n';
            }
        }

        uint cursor = 0;
        std::string key;
        while (files.find(':', cursor + 1) != files.npos){

            cursor = files.find(':', cursor + 1);
            char32_t character{'\0'};

            bool skip = false;

            // read name
            for (uint i = cursor - 1; i > 0; --i) {
                character = files[i];
                if (character != U' '){

                    if (character == '"'){
                        skip = true;
                        break;
                    }

                    std::string name{};
                    for (int j = i; j >= -1; --j) {
                        if (j == -1){
                            key = name;
                            break;
                        }
                        character = files[j];
                        if (character != U'-' && character != U' ' && character != U'\n' && character != U'\t'){
                            name.insert(name.begin(), character);
                        } else if(character == U'-'){
                            nowLanguage = &LocalizationSystem::text[name];
                            break;
                        } else{
                            key = name;
                            break;
                        }
                    }
                    break;
                }
            }

            if (skip) continue;

            //read files

            std::u32string text{};

            for (int i = cursor + 1; i < files.size(); ++i) {
                character = files[i];
                if (character != U' ' && character != U'\n' && character != U'\t'){
                    if (character == U'"'){
                        bool spec = false;
                        for (int j = i + 1; j < files.size(); ++j) {
                            character  = files[j];
                            if (character == '\\'){
                                spec = true;
                            } else if (spec){
                                switch (character) {
                                    case U'"':
                                        text += character;
                                        break;
                                    case U'n':
                                        text += U'\n';
                                        break;
                                    case U't':
                                        text += U'\t';
                                        break;
                                }
                                spec = false;
                            } else{
                                if (character == '"'){
                                    (*nowLanguage)[key] = text;
                                    break;
                                } else{
                                    text += character;
                                }
                            }
                        }
                    } else{
                        break;
                    }
                }
            }
        }
    }

    void LocalizationSystem::setNowLanguage(std::string nowLanguage) {
        LocalizationSystem::nowLanguage = &text[nowLanguage];
    }

    std::u32string LocalizationSystem::getText(std::string key) {
        return (*LocalizationSystem::nowLanguage)[key];
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