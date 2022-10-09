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
            if (!isKeyPressed(key)) {
                press = false;
                break;
            }
        }
        if (press){
            for (auto& key : blackListKeys) {
                if (isKeyPressed(key)) {
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

    ButtonsInteraction *ButtonsInteraction::createFromYaml(const YAML::Node &node) {
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

        return new ButtonsInteraction{event, keys, blackListKeys};
    }
} // ui