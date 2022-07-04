#include "sizing.h"

float ui::Sizing::operator()(float parentSize, float targetSize) {
	return this->findSize(parentSize, targetSize);
}
