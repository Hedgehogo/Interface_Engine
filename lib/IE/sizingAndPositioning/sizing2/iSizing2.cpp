#include "iSizing2.hpp"

namespace ui {
	sf::Vector2f ISizing2::operator()(sf::Vector2f parentSize) {
		return this->findSize(parentSize);
	}
}