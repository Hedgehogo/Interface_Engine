#include "FnSizing.hpp"

#include <utility>

namespace ie {
	FnSizing::Make::Make(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn) :
		findSizeFn(std::move(findSizeFn)), getParentSizeFn(std::move(getParentSizeFn)){
	}
	
	FnSizing* FnSizing::Make::make(float normalSize) {
		return new FnSizing{std::move(*this), normalSize};
	}
	
	FnSizing::FnSizing(Make&& make, float normalSize) :
		findSizeFn(std::move(make.findSizeFn)), getParentSizeFn(std::move(make.getParentSizeFn)), normalSize(normalSize) {
	}
	
	FnSizing::FnSizing(FindSizeFn findSizeFn, GetParentSizeFn getParentSizeFn) :
		findSizeFn(std::move(findSizeFn)), getParentSizeFn(std::move(getParentSizeFn)), normalSize() {
	}
	
	void FnSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float FnSizing::findSize(float parentSize, float targetSize) {
		return findSizeFn(parentSize, targetSize, normalSize);
	}
	
	float FnSizing::getParentSize(float objectMinSize) {
		return getParentSizeFn(objectMinSize);
	}
	
	FnSizing* FnSizing::copy() {
		return new FnSizing{*this};
	}
}