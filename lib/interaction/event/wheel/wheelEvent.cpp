#include "wheelEvent.h"
namespace sf::Wheel {
	int value;
}
ui::WheelEvent::WheelEvent() : active(false) {}

void ui::WheelEvent::copy(ui::WheelEvent *wheelEvent) {
	wheelEvent->active = this->active;
}
