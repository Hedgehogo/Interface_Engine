#include "positioning.h"

float ui::Positioning::operator()(float parentPosition, float objectSize, float parentSize, float targetSize) {
	return this->findPosition(parentPosition, objectSize, parentSize, targetSize);
}
