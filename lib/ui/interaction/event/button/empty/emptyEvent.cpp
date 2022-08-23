#include "emptyEvent.h"

ui::EmptyEvent::EmptyEvent() : ButtonEvent() {}

void ui::EmptyEvent::update(sf::Vector2i mousePosition, bool press) {}

ui::EmptyEvent *ui::EmptyEvent::copy() {
	EmptyEvent* emptyEvent{new EmptyEvent{}};
	ButtonEvent::copy(emptyEvent);
	return emptyEvent;
}
