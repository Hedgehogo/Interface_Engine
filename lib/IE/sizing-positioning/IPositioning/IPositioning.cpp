#include "IPositioning.hpp"

namespace ie {
	auto IPositioning::operator()(float parent_position, float object_size, float parent_size, float target_size) -> float {
		return this->find_position(parent_position, object_size, parent_size, target_size);
	}
}
