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
	
	RelativeParentSizing *RelativeParentSizing::createFromYaml(const YAML::Node &node) {
		float addition;
		node["addition"] >> addition;
		return new RelativeParentSizing{addition};
	}
}