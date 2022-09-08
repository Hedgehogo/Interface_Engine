#include "switchEvent.hpp"

#include "../switch.hpp"

namespace ui {
    SwitchEvent::SwitchEvent(Switch &switcher) : switcher(&switcher) {}

    void SwitchEvent::startPressed() {}

    void SwitchEvent::stopPressed() {
        switcher->switchValue();
    }

    void SwitchEvent::whilePressed() {}

    void SwitchEvent::whileNotPressed() {}

    void SwitchEvent::setSwitcher(Switch &switcher) {
        this->switcher = &switcher;
    }

    SwitchEvent *SwitchEvent::copy() {
        return new SwitchEvent(*switcher);
    }

}