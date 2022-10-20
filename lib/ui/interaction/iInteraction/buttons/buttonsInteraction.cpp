#include "buttonsInteraction.hpp"

namespace ui {
    ButtonsInteraction::ButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys) : event(event), keys(keys), blackListKeys(blackListKeys), press(false) {
        std::sort(this->keys.begin(), this->keys.end());
    }

    ButtonsInteraction::~ButtonsInteraction() {
        delete event;
    }

    std::vector<Key> ButtonsInteraction::getKeys() {
        return keys;
    }

    ButtonEvent *ButtonsInteraction::getEvent() {
        return event;
    }

    void ButtonsInteraction::setEvent(ButtonEvent *event) {
        delete this->event;
        this->event = event;
    }

    void ButtonsInteraction::start(sf::Vector2i) {}

    bool ButtonsInteraction::update(sf::Vector2i mousePosition) {
        press = true;
        for (auto& key : keys) {
            if (!KeyHandler::isKeyPressed(key)) {
                press = false;
                break;
            }
        }
        if (press){
            for (auto& key : blackListKeys) {
                if (KeyHandler::isKeyPressed(key)) {
                    press = false;
                    break;
                }
            }
        }
        event->update(mousePosition, press);
        return false;
    }

    void ButtonsInteraction::finish(sf::Vector2i mousePosition) {
        event->setPressed(false);
    }

    ButtonsInteraction *ButtonsInteraction::copy() {
        return new ButtonsInteraction{event->copy(), keys, blackListKeys};
    }

    bool ButtonsInteraction::isPress() {
        return press;
    }

    bool convertPointer(const YAML::Node &node, ButtonsInteraction *&buttonsInteraction) {
        ButtonEvent *event;
        std::vector<Key> keys;
        std::vector<Key> blackListKeys{};

        node["event"] >> event;

        keys.resize(node["keys"].size());
        uint i{0};
        for (auto &key: node["keys"]) {
            key >> keys[i];
            ++i;
        }

        if (node["black-listKeys"]){
            i = 0;
            for (auto& key : node["black-listKeys"]) {
                key >> blackListKeys[i];
                ++i;
            }
        }

        { buttonsInteraction = new ButtonsInteraction{event, keys, blackListKeys}; return true; }
    }
} // ui