#include "iPositioning.hpp"

namespace ui {
	float IPositioning::operator()(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return this->findPosition(parentPosition, objectSize, parentSize, targetSize);
	}
}
