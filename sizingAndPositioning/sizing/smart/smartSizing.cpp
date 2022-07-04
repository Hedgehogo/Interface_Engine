#include "smartSizing.h"

namespace ui {
	SmartSizing::SmartSizing(float targetCoefficient, float parentCoefficient, float addition) :
		targetCoefficient(targetCoefficient), parentCoefficient(parentCoefficient), addition(addition) {}
	
	void SmartSizing::init(float) {}
	
	float SmartSizing::findSize(float parentSize, float targetSize) {
		return parentSize * parentCoefficient + targetSize * targetCoefficient + addition;
	}
	
	SmartSizing *SmartSizing::copy() {
		return new SmartSizing{targetCoefficient, parentCoefficient, addition};
	}
	
	Sizing *createSizing(float targetCoefficient, float parentCoefficient, float addition) {
		return new SmartSizing{targetCoefficient, parentCoefficient, addition};
	}
}