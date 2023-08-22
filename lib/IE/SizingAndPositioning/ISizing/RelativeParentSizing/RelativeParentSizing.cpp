#include "RelativeParentSizing.hpp"

namespace ui {
	RelativeParentSizing::Make::Make(float addition) : addition(addition) {
	}
	
	RelativeParentSizing* RelativeParentSizing::Make::make(float normalSize) {
		return new RelativeParentSizing{std::move(*this), normalSize};
	}
	
	RelativeParentSizing::RelativeParentSizing(Make&& make, float) :
		addition(make.addition) {
	}
	
	RelativeParentSizing::RelativeParentSizing(float addition) : addition(addition) {
	}
	
	void RelativeParentSizing::init(float) {
	}
	
	float RelativeParentSizing::findSize(float parentSize, float) {
		return parentSize + addition;
	}
	
	float RelativeParentSizing::getParentSize(float objectSize) {
		return objectSize - addition;
	}
	
	RelativeParentSizing* RelativeParentSizing::copy() {
		return new RelativeParentSizing{*this};
	}
	
	bool DecodePointer<RelativeParentSizing>::decodePointer(const YAML::Node& node, RelativeParentSizing*& relativeParentSizing) {
		relativeParentSizing = new RelativeParentSizing{node["addition"].as<float>()};
		return true;
	}
}