#include "targetCoefficientSizing.h"

namespace ui {
	TargetCoefficientSizing::TargetCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {}
	
	void TargetCoefficientSizing::init(float) {}
	
	float TargetCoefficientSizing::findSize(float, float targetSize) {
		return targetSize * coefficient + addition;
	}
	
	TargetCoefficientSizing *TargetCoefficientSizing::copy() {
		return new TargetCoefficientSizing{coefficient, addition};
	}
}