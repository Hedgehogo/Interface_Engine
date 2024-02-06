#include "INonInteractiveObject.hpp"

namespace ie {
	bool INonInteractiveObject::update_interactions(sf::Vector2f mouse_position) {
		return INonInteractive::update_interactions(mouse_position);
	}
}
