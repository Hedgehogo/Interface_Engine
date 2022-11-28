#include "smartSizing.hpp"

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
	
	float SmartSizing::getParentSize(float objectSize) {
		return (objectSize - addition) / parentCoefficient;
	}
	
	bool convertPointer(const YAML::Node &node, SmartSizing *&smartSizing) {
		float targetCoefficient{1.f};
		float parentCoefficient{0.f};
		float addition{0.f};
		
		if(node["target-coefficient"])
			node["target-coefficient"] >> targetCoefficient;
		if(node["parent-coefficient"])
			node["parent-coefficient"] >> parentCoefficient;
		if(node["addition"])
			node["addition"] >> addition;
		
		{ smartSizing = new SmartSizing{targetCoefficient, parentCoefficient, addition}; return true; }
	}
}