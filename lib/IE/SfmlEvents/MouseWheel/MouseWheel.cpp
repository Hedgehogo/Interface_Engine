#include <iostream>
#include "MouseWheel.hpp"

namespace ui {
	sf::Vector2f MouseWheel::delta{0, 0};
	
	void MouseWheel::setDelta(sf::Event::MouseWheelScrollEvent event) {
		if(event.wheel == sf::Mouse::Wheel::VerticalWheel) {
			delta.y += event.delta;
		} else {
			delta.x += event.delta;
		}
	}
	
	void MouseWheel::setDelta(sf::Vector2f delta) {
		MouseWheel::delta = delta;
	}
	
	void MouseWheel::clear() {
		delta = {0, 0};
	}
	
	sf::Vector2f MouseWheel::getDelta() {
		return delta;
	}
}