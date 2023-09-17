#include "MatchSidesPositioning.hpp"

namespace ie {
	MatchSidesPositioning::MatchSidesPositioning(Location parentSide, Location objectSide, float offset) : parentSide(parentSide), objectSide(objectSide), offset(offset) {
	}
	
	float MatchSidesPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		float position{parentPosition + offset};
		switch(parentSide) {
			case Location::Origin:
				break;
			case Location::Center:
				position += parentSize * 0.5f;
				break;
			case Location::End:
				position += parentSize;
				break;
		}
		switch(objectSide) {
			case Location::Origin:
				break;
			case Location::Center:
				position -= objectSize * 0.5f;
				break;
			case Location::End:
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
}