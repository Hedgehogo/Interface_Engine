#include "lambdaSizing.h"

namespace ui {
	LambdaSizing::LambdaSizing(float (*findSize)(float parentSize, float targetSize, float normalSize)) : sizing(findSize) {}
	
	void LambdaSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float LambdaSizing::findSize(float parentSize, float targetSize) {
		return sizing(parentSize, targetSize, normalSize);
	}
	
	void LambdaSizing::copy(LambdaSizing *lambdaSizing) {
		lambdaSizing->normalSize = this->normalSize;
	}
	
	LambdaSizing *LambdaSizing::copy() {
		LambdaSizing* lambdaSizing{new LambdaSizing{sizing}};
		LambdaSizing::copy(lambdaSizing);
		return lambdaSizing;
	}
}