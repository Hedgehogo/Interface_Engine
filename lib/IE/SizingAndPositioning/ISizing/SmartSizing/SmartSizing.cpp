#include "SmartSizing.hpp"

namespace ui {
	SmartSizing::Make::Make(float targetCoefficient, float parentCoefficient, float addition) :
		targetCoefficient(targetCoefficient), parentCoefficient(parentCoefficient), addition(addition) {
	}
	
	SmartSizing* SmartSizing::Make::make(float normalSize) {
		return new SmartSizing{std::move(*this), normalSize};
	}
	
	SmartSizing::SmartSizing(SmartSizing::Make&& make, float) :
		targetCoefficient(make.targetCoefficient), parentCoefficient(make.parentCoefficient), addition(make.addition) {
	}
	
	SmartSizing::SmartSizing(float targetCoefficient, float parentCoefficient, float addition) :
		targetCoefficient(targetCoefficient), parentCoefficient(parentCoefficient), addition(addition) {
	}
	
	void SmartSizing::init(float) {
	}
	
	float SmartSizing::findSize(float parentSize, float targetSize) {
		return parentSize * parentCoefficient + targetSize * targetCoefficient + addition;
	}
	
	SmartSizing* SmartSizing::copy() {
		return new SmartSizing{*this};
	}
	
	float SmartSizing::getParentSize(float objectSize) {
		return (objectSize - addition) / parentCoefficient;
	}
	
	bool DecodePointer<SmartSizing>::decodePointer(const YAML::Node& node, SmartSizing*& smartSizing) {
		smartSizing = new SmartSizing{
			convDef(node["target-coefficient"], 1.f),
			convDef(node["parent-coefficient"], 0.f),
			convDef(node["addition"], 0.f)
		};
		return true;
	}
}