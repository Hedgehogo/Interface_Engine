#include "positioning.hpp"

namespace ui {
	float Positioning::operator()(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return this->findPosition(parentPosition, objectSize, parentSize, targetSize);
	}
}
