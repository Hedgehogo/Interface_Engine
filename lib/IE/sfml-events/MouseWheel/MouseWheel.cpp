#include <iostream>
#include "MouseWheel.hpp"

namespace ie {
	sf::Vector2f MouseWheel::delta_{0, 0};
	
	auto MouseWheel::set_delta(sf::Event::MouseWheelScrollEvent event) -> void {
		if(event.wheel == sf::Mouse::Wheel::VerticalWheel) {
			delta_.y += event.delta;
		} else {
			delta_.x += event.delta;
		}
	}
	
	auto MouseWheel::set_delta(sf::Vector2f delta) -> void {
		MouseWheel::delta_ = delta;
	}
	
	auto MouseWheel::clear() -> void {
		delta_ = {0, 0};
	}
	
	auto MouseWheel::get_delta() -> sf::Vector2f {
		return delta_;
	}
}