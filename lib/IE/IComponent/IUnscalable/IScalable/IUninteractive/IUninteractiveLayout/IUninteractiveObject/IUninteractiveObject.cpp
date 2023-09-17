#include "IUninteractiveObject.hpp"

namespace ie {
	bool IUninteractiveObject::updateInteractions(sf::Vector2f mousePosition) {
		return IUninteractive::updateInteractions(mousePosition);
	}
}
