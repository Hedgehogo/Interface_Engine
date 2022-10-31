#pragma once

#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
    class KeysInteraction : public virtual IInteraction{
    protected:
        bool press;

        KeyEvent *event;
        std::vector<Key> keys;
        std::vector<Key> blackListKeys;

    public:
        KeysInteraction(KeyEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});

        bool isPress();

        std::vector<Key> getKeys();

        KeyEvent* getEvent();

        void setEvent(KeyEvent *event);

        void start(sf::Vector2i mousePosition) override;

        void update(sf::Vector2i mousePosition) override;

        void finish(sf::Vector2i mousePosition) override;

        KeysInteraction* copy() override;

        ~KeysInteraction() override;

    };
	
	bool convertPointer(const YAML::Node &node, KeysInteraction *&keysInteraction);

} // ui