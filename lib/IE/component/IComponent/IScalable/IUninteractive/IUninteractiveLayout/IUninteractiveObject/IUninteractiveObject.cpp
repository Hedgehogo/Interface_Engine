#include "IUninteractiveObject.hpp"

namespace ie {
	bool IUninteractiveObject::update_interactions(sf::Vector2f mouse_position) {
		return IUninteractive::update_interactions(mouse_position);
	}
}
