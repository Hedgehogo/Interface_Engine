#include "matchSidesPositioning.hpp"

namespace ui {
	
	MatchSidesPositioning::MatchSidesPositioning(Location parentSide, Location objectSide, float offset) : parentSide(parentSide), objectSide(objectSide), offset(offset) {}
	
	float MatchSidesPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		float position{parentPosition + offset};
		switch(parentSide) {
			case Location::origin: break;
			case Location::center: position += parentSize * 0.5f; break;
			case Location::end: position += parentSize; break;
		}
		switch(objectSide) {
			case Location::origin: break;
			case Location::center: position -= objectSize * 0.5f; break;
			case Location::end: position -= objectSize; break;
		}
		return position;
	}
	
	MatchSidesPositioning *MatchSidesPositioning::copy() {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
	
	MatchSidesPositioning *MatchSidesPositioning::createFromYaml(const YAML::Node &node) {
		Location parentSide;
		Location objectSide;
		float offset{0.f};
		
		parentSide = createLocationFromYaml(node["parent-side"]);
		objectSide = createLocationFromYaml(node["object-side"]);
		if(node["offset"])
			node["offset"] >> offset;
		
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
	
	Positioning *createPosition(Location parentSide, Location objectSide, float offset) {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
}