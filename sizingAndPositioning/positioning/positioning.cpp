#include "positioning.h"

float ui::Positioning::operator()(float parentPosition, float parentSize, float objectSize) {
	return this->findPosition(parentPosition, parentSize, objectSize);
}
