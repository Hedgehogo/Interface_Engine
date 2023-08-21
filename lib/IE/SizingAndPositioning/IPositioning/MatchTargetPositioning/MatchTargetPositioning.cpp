#include "MatchTargetPositioning.hpp"

namespace ui {
	MatchTargetPositioning::MatchTargetPositioning(float targetCoefficient, float objectCoefficient, float offset) : targetCoefficient(targetCoefficient), objectCoefficient(objectCoefficient), offset(offset) {
	}
	
	float MatchTargetPositioning::findPosition(float, float objectSize, float, float targetSize) {
		return targetSize * targetCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchTargetPositioning* MatchTargetPositioning::copy() {
		return new MatchTargetPositioning{*this};
	}
	
	bool DecodePointer<MatchTargetPositioning>::decodePointer(const YAML::Node& node, MatchTargetPositioning*& matchTargetPositioning) {
		matchTargetPositioning = new MatchTargetPositioning{
			node["target-coefficient"].as<float>(),
			node["object-coefficient"].as<float>(),
			convDef(node["offset"], 0.f)
		};
		return true;
	}
}