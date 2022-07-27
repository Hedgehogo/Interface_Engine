#include "switchEvent.h"

#include "../switch.h"

namespace ui {
    SwitchEvent::SwitchEvent(Switch &switcher) : switcher(&switcher) {}

    void SwitchEvent::startPressed(sf::Vector2i mousePosition) {}

    void SwitchEvent::stopPressed(sf::Vector2i mousePosition) {
        switcher->switchValue();
    }

    void SwitchEvent::whilePressed(sf::Vector2i mousePosition) {}

    void SwitchEvent::whileNotPressed(sf::Vector2i mousePosition) {}

    void SwitchEvent::setSwitcher(Switch &switcher) {
        this->switcher = &switcher;
    }

    SwitchEvent *SwitchEvent::copy() {
        return new SwitchEvent(*switcher);
    }

}