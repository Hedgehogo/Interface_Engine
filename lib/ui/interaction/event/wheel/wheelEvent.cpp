#include "wheelEvent.hpp"

namespace sf::Wheel {
	int value;
}

namespace ui {
	WheelEvent::WheelEvent() : active(false) {
	}
	
	void WheelEvent::copy(WheelEvent* wheelEvent) {
		wheelEvent->active = this->active;
	}
}
