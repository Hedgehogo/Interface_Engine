#include "ISizing2.hpp"

namespace ie {
	auto ISizing2::operator()(sf::Vector2f parent_size) -> sf::Vector2f {
		return this->find_size(parent_size);
	}
}