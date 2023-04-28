#include "matchTargetPositioning.hpp"

namespace ui {
	MatchTargetPositioning::MatchTargetPositioning(float targetCoefficient, float objectCoefficient, float offset) : targetCoefficient(targetCoefficient), objectCoefficient(objectCoefficient), offset(offset) {
	}
	
	float MatchTargetPositioning::findPosition(float parentPosition, float objectSize, float, float targetSize) {
		return targetSize * targetCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchTargetPositioning* MatchTargetPositioning::copy() {
		return new MatchTargetPositioning{targetCoefficient, objectCoefficient, offset};
	}
	
	
	bool DecodePointer<MatchTargetPositioning>::decodePointer(const YAML::Node& node, MatchTargetPositioning*& matchTargetPositioning) {
		float targetCoefficient;
		float objectCoefficient;
		float offset{0.f};
		
		node["target-coefficient"] >> targetCoefficient;
		node["object-coefficient"] >> objectCoefficient;
		if(node["offset"])
			node["offset"] >> offset;
		
		{
			matchTargetPositioning = new MatchTargetPositioning{targetCoefficient, objectCoefficient, offset};
			return true;
		}
	}
}