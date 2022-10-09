#include "textButtonsInteraction.hpp"
#include "../../text.h"
namespace ui {
    TextButtonsInteraction::TextButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys) : ButtonsInteraction(event, keys, blackListKeys) {}

    void TextButtonsInteraction::init(Text *text) {
        TextInteraction::init(text);
        dynamic_cast<TextEvent *>(event)->init(text);
    }

    TextButtonsInteraction *TextButtonsInteraction::copy() {
        return new TextButtonsInteraction{event, keys, blackListKeys};
    }

    TextButtonsInteraction* TextButtonsInteraction::createFromYaml(const YAML::Node &node){
        ButtonEvent *event;
        std::vector<Key> keys;
        std::vector<Key> blackListKeys{};

        node["event"] >> event;

        keys.resize(node["keys"].size());
        uint i{0};
        for (auto &key: node["keys"]) {
            keys[i] = createKeyFromYaml(key);
            ++i;
        }

        if (node["black-listKeys"]){
            i = 0;
            for (auto& key : node["black-listKeys"]) {
                blackListKeys[i] = createKeyFromYaml(key);
                ++i;
            }
        }

        return new TextButtonsInteraction{event, keys, blackListKeys};
    }
} // ui