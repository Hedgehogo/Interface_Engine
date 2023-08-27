#include "ISizing2.hpp"

namespace ie {
	sf::Vector2f ISizing2::operator()(sf::Vector2f parentSize) {
		return this->findSize(parentSize);
	}
}