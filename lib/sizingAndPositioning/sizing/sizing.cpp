#include "sizing.h"

float ui::Sizing::getParentSize(float objectSize) {
	return 0;
}

float ui::Sizing::operator()(float parentSize, float targetSize) {
	return this->findSize(parentSize, targetSize);
}
