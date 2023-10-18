#include "IPositioning.hpp"

namespace ie {
	float IPositioning::operator()(float parent_position, float object_size, float parent_size, float target_size) {
		return this->find_position(parent_position, object_size, parent_size, target_size);
	}
}
