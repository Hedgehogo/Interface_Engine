#include "INonInteractiveObject.hpp"

namespace ie {
	auto INonInteractiveObject::update_interactions(sf::Vector2f mouse_position) -> bool {
		return INonInteractive::update_interactions(mouse_position);
	}
}
