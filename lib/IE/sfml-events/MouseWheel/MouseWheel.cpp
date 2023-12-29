#include <iostream>
#include "MouseWheel.hpp"

namespace ie {
	sf::Vector2f MouseWheel::delta_{0, 0};
	
	void MouseWheel::set_delta(sf::Event::MouseWheelScrollEvent event) {
		if(event.wheel == sf::Mouse::Wheel::VerticalWheel) {
			delta_.y += event.delta;
		} else {
			delta_.x += event.delta;
		}
	}
	
	void MouseWheel::set_delta(sf::Vector2f delta) {
		MouseWheel::delta_ = delta;
	}
	
	void MouseWheel::clear() {
		delta_ = {0, 0};
	}
	
	sf::Vector2f MouseWheel::get_delta() {
		return delta_;
	}
}