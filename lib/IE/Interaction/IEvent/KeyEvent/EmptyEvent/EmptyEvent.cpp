#include "EmptyEvent.hpp"

namespace ui {
	EmptyEvent::EmptyEvent() : KeyEvent() {
	}
	
	void EmptyEvent::update(sf::Vector2i, bool) {
	}
	
	EmptyEvent* EmptyEvent::copy() {
		return new EmptyEvent{*this};
	}
}
