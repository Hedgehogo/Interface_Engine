#include "IPositioning.hpp"

namespace ie {
	float IPositioning::operator()(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return this->findPosition(parentPosition, objectSize, parentSize, targetSize);
	}
}
