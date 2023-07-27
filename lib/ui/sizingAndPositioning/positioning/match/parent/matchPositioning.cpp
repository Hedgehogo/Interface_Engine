#include "matchPositioning.hpp"

namespace ui {
	MatchPositioning::MatchPositioning(float parentCoefficient, float objectCoefficient, float offset) : parentCoefficient(parentCoefficient), objectCoefficient(objectCoefficient), offset(offset) {
	}
	
	float MatchPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return parentPosition + parentSize * parentCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchPositioning* MatchPositioning::copy() {
		return new MatchPositioning{parentCoefficient, objectCoefficient, offset};
	}
	
	bool DecodePointer<MatchPositioning>::decodePointer(const YAML::Node& node, MatchPositioning*& matchPositioning) {
		float parentCoefficient;
		float objectCoefficient;
		float offset{0.f};
		
		node["parent-coefficient"] >> parentCoefficient;
		node["object-coefficient"] >> objectCoefficient;
		if(node["offset"])
			node["offset"] >> offset;
		
		{
			matchPositioning = new MatchPositioning{parentCoefficient, objectCoefficient, offset};
			return true;
		}
	}
}