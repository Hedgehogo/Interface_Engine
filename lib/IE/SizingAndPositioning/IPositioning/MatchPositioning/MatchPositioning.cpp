#include "MatchPositioning.hpp"

namespace ie {
	MatchPositioning::MatchPositioning(float parentCoefficient, float objectCoefficient, float offset) : parentCoefficient(parentCoefficient), objectCoefficient(objectCoefficient), offset(offset) {
	}
	
	float MatchPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		return parentPosition + parentSize * parentCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchPositioning* MatchPositioning::copy() {
		return new MatchPositioning{*this};
	}
	
	bool DecodePointer<MatchPositioning>::decodePointer(const YAML::Node& node, MatchPositioning*& matchPositioning) {
		matchPositioning = new MatchPositioning{
			node["parent-coefficient"].as<float>(),
			node["object-coefficient"].as<float>(),
			convDef(node["offset"], 0.f)
		};
		return true;
	}
}