#include "emptyEvent.hpp"

namespace ui {
	EmptyEvent::EmptyEvent() : KeyEvent() {
	}
	
	void EmptyEvent::update(sf::Vector2i, bool) {
	}
	
	EmptyEvent* EmptyEvent::copy() {
		EmptyEvent* emptyEvent{new EmptyEvent{}};
		KeyEvent::copy(emptyEvent);
		return emptyEvent;
	}
}
