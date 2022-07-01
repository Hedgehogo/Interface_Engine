#include "constSizing.h"

namespace ui {
	ConstSizing::ConstSizing(float size) : size(size) {}
	
	void ConstSizing::init(sf::RenderTarget &, float) {}
	
	float ConstSizing::findSize(float) {
		return this->size;
	}
	
	ConstSizing *ConstSizing::copy() {
		return new ConstSizing(size);
	}
	
	Sizing *size(float constSize) {
		return new ConstSizing{constSize};
	}
}