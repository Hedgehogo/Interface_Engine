#include "baseSizing2.hpp"

namespace ui {
	sf::Vector2f BaseSizing2::operator()(sf::Vector2f parentSize) {
		return this->findSize(parentSize);
	}
}