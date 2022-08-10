#include "wheelEvent.hpp"
namespace sf::Wheel {
	int value;
}
ui::WheelEvent::WheelEvent() : active(false) {}

void ui::WheelEvent::copy(ui::WheelEvent *wheelEvent) {
	wheelEvent->active = this->active;
}

ui::WheelEvent *ui::WheelEvent::createFromYaml(const YAML::Node &node) {
    return nullptr;
}
