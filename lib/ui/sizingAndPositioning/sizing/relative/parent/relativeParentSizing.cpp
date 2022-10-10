//
// Created by Professional on 30.06.2022.
//

#include "relativeParentSizing.hpp"

namespace ui {
	RelativeParentSizing::RelativeParentSizing(float addition) : addition(addition) {}
	
	void RelativeParentSizing::init(float) {}
	
	float RelativeParentSizing::findSize(float parentSize, float) {
		return parentSize + addition;
	}
	
	float RelativeParentSizing::getParentSize(float objectSize) {
		return objectSize - addition;
	}
	
	RelativeParentSizing *RelativeParentSizing::copy() {
		return new RelativeParentSizing{addition};
	}
	
	bool convertPointer(const YAML::Node &node, RelativeParentSizing *&relativeParentSizing) {
		float addition;
		node["addition"] >> addition;
		{ relativeParentSizing = new RelativeParentSizing{addition}; return true; }
	}
}