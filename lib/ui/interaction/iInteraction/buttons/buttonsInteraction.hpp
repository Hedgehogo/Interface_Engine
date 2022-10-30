#pragma once

#include "../iInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
#include "../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {

    class ButtonsInteraction : public virtual IInteraction{
    protected:
        bool press;

        ButtonEvent *event;
        std::vector<Key> keys;
        std::vector<Key> blackListKeys;

    public:
        ButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});

        bool isPress();

        std::vector<Key> getKeys();

        ButtonEvent* getEvent();

        void setEvent(ButtonEvent *event);

        void start(sf::Vector2i mousePosition) override;

        void update(sf::Vector2i mousePosition) override;

        void finish(sf::Vector2i mousePosition) override;

        ButtonsInteraction* copy() override;

        ~ButtonsInteraction() override;

    };
	
	bool convertPointer(const YAML::Node &node, ButtonsInteraction *&buttonsInteraction);

} // ui