#include "ISizing.hpp"

namespace ie {
	float ISizing::getParentSize(float) {
		return 0;
	}
	
	float ISizing::operator()(float parentSize, float targetSize) {
		return this->findSize(parentSize, targetSize);
	}
}
