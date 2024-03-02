#include "ISizing.hpp"

namespace ie {
	auto ISizing::get_parent_size(float) -> float {
		return 0;
	}
	
	auto ISizing::operator()(float parent_size, float target_size) -> float {
		return this->find_size(parent_size, target_size);
	}
}
