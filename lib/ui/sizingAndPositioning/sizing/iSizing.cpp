#include "iSizing.hpp"

namespace ui {
	float ISizing::getParentSize(float objectSize) {
		return 0;
	}
	
	float ISizing::operator()(float parentSize, float targetSize) {
		return this->findSize(parentSize, targetSize);
	}
}
