#include "LambdaSizing.hpp"

#include <utility>

namespace ui {
	LambdaSizing::Make::Make(LambdaSizing::FindSizeFunc findSizeFunc, LambdaSizing::MinSizeFunc minSizeFunc) :
		findSizeFunc(std::move(findSizeFunc)), minSizeFunc(std::move(minSizeFunc)){
	}
	
	LambdaSizing* LambdaSizing::Make::make(float normalSize) {
		return new LambdaSizing{std::move(*this), normalSize};
	}
	
	LambdaSizing::LambdaSizing(Make&& make, float normalSize) :
		findSizeFunc(std::move(make.findSizeFunc)), minSizeFunc(std::move(make.minSizeFunc)), normalSize(normalSize) {
	}
	
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
	
	LambdaSizing* LambdaSizing::copy() {
		return new LambdaSizing{*this};
	}
}