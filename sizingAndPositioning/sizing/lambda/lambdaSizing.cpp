#include "lambdaSizing.h"

namespace ui {
	LambdaSizing::LambdaSizing(float (*findSize)(float parentSize, float targetSize, float normalSize), float (*getParentMinSize)(float objectMinSize)) : sizing(findSize), minSize(getParentMinSize) {}
	
	void LambdaSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float LambdaSizing::findSize(float parentSize, float targetSize) {
		return sizing(parentSize, targetSize, normalSize);
	}
	
	float LambdaSizing::getParentMinSize(float objectMinSize) {
		return minSize(objectMinSize);
	}
	
	void LambdaSizing::copy(LambdaSizing *lambdaSizing) {
		lambdaSizing->normalSize = this->normalSize;
	}
	
	LambdaSizing *LambdaSizing::copy() {
		LambdaSizing* lambdaSizing{new LambdaSizing{sizing, minSize}};
		LambdaSizing::copy(lambdaSizing);
		return lambdaSizing;
	}
}