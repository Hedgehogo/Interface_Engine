#include "parentCoefficientSizing.h"

namespace ui {
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {}
	
	void ParentCoefficientSizing::init(float) {}
	
	float ParentCoefficientSizing::findSize(float parentSize, float) {
		return parentSize * coefficient + addition;
	}
	
	ParentCoefficientSizing *ParentCoefficientSizing::copy() {
		return new ParentCoefficientSizing{coefficient, addition};
	}
	
	float ParentCoefficientSizing::getParentMinSize(float objectMinSize) {
		return (objectMinSize - addition) / coefficient;
	}
}