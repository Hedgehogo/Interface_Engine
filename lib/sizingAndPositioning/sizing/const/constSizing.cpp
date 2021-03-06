#include "constSizing.h"

namespace ui {
	ConstSizing::ConstSizing(float size) : size(size) {}
	
	void ConstSizing::init(float) {}
	
	float ConstSizing::findSize(float, float) {
		return this->size;
	}
	
	ConstSizing *ConstSizing::copy() {
		return new ConstSizing(size);
	}
	
	Sizing *size(float constSize) {
		return new ConstSizing{constSize};
	}
}