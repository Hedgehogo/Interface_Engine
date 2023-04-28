#include "lambdaSizing.hpp"

#include <utility>

namespace ui {
	LambdaSizing::LambdaSizing(FindSizeFunc findSizeFunc, MinSizeFunc minSizeFunc) :
		findSizeFunc(std::move(findSizeFunc)), minSizeFunc(std::move(minSizeFunc)), normalSize() {
	}
	
	void LambdaSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float LambdaSizing::findSize(float parentSize, float targetSize) {
		return findSizeFunc(parentSize, targetSize, normalSize);
	}
	
	float LambdaSizing::getParentSize(float objectMinSize) {
		return minSizeFunc(objectMinSize);
	}
	
	void LambdaSizing::copy(LambdaSizing* lambdaSizing) {
		lambdaSizing->normalSize = this->normalSize;
	}
	
	LambdaSizing* LambdaSizing::copy() {
		LambdaSizing* lambdaSizing{new LambdaSizing{findSizeFunc, minSizeFunc}};
		LambdaSizing::copy(lambdaSizing);
		return lambdaSizing;
	}
}