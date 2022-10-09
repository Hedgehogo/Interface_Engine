#include "emptyEvent.hpp"

namespace ui {
	EmptyEvent::EmptyEvent() : ButtonEvent() {}
	
	void EmptyEvent::update(sf::Vector2i mousePosition, bool press) {}
	
	EmptyEvent *EmptyEvent::copy() {
		EmptyEvent *emptyEvent{new EmptyEvent{}};
		ButtonEvent::copy(emptyEvent);
		return emptyEvent;
	}
}
