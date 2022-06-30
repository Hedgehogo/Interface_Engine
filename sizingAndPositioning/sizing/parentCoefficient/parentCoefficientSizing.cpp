#include "parentCoefficientSizing.h"

namespace ui {
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {}
	
	void ParentCoefficientSizing::init(sf::RenderTarget &, float) {}
	
	float ParentCoefficientSizing::findSize(float parentSize) {
		return parentSize * coefficient + addition;
	}
	
	ParentCoefficientSizing *ParentCoefficientSizing::copy() {
		return new ParentCoefficientSizing{coefficient, addition};
	}
	
	Sizing *createSize(float coefficient, float addition) {
		return new ParentCoefficientSizing{coefficient, addition};
	}
}