#include "sizing.hpp"

namespace ui {
	float Sizing::getParentSize(float objectSize) {
		return 0;
	}
	
	float Sizing::operator()(float parentSize, float targetSize) {
		return this->findSize(parentSize, targetSize);
	}
}
