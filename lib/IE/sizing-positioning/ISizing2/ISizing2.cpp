#include "ISizing2.hpp"

namespace ie {
	sf::Vector2f ISizing2::operator()(sf::Vector2f parent_size) {
		return this->find_size(parent_size);
	}
}