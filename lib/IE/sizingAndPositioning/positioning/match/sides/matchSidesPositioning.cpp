#include "matchSidesPositioning.hpp"

namespace ui {
	MatchSidesPositioning::MatchSidesPositioning(Location parentSide, Location objectSide, float offset) : parentSide(parentSide), objectSide(objectSide), offset(offset) {
	}
	
	float MatchSidesPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		float position{parentPosition + offset};
		switch(parentSide) {
			case Location::origin:
				break;
			case Location::center:
				position += parentSize * 0.5f;
				break;
			case Location::end:
				position += parentSize;
				break;
		}
		switch(objectSide) {
			case Location::origin:
				break;
			case Location::center:
				position -= objectSize * 0.5f;
				break;
			case Location::end:
				position -= objectSize;
				break;
		}
		return position;
	}
	
	MatchSidesPositioning* MatchSidesPositioning::copy() {
		return new MatchSidesPositioning{*this};
	}
	
	bool DecodePointer<MatchSidesPositioning>::decodePointer(const YAML::Node& node, MatchSidesPositioning*& matchSidesPositioning) {
		matchSidesPositioning = new MatchSidesPositioning{
			node["parent-side"].as<Location>(),
			node["object-side"].as<Location>(),
			convDef(node["offset"], 0.f)
		};
		return true;
	}
	
	/*Positioning *makePosition(Location parentSide, Location objectSide, float offset) {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}*/
}