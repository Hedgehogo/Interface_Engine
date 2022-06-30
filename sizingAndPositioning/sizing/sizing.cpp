#include "sizing.h"

float ui::Sizing::operator()(float parentSize) {
	return this->findSize(parentSize);
}
