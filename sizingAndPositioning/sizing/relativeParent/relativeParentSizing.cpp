//
// Created by Professional on 30.06.2022.
//

#include "relativeParentSizing.h"

namespace ui {
	RelativeParentSizing::RelativeParentSizing(float addition) : addition(addition) {}
	
	void RelativeParentSizing::init(sf::RenderTarget &, float) {}
	
	float RelativeParentSizing::findSize(float parentSize) {
		return parentSize + addition;
	}
	
	RelativeParentSizing *RelativeParentSizing::copy() {
		return new RelativeParentSizing{addition};
	}
}