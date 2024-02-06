#include "ISizing.hpp"

namespace ie {
	float ISizing::get_parent_size(float) {
		return 0;
	}
	
	float ISizing::operator()(float parent_size, float target_size) {
		return this->find_size(parent_size, target_size);
	}
}
