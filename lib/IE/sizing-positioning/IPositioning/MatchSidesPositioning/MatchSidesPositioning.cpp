#include "MatchSidesPositioning.hpp"

namespace ie {
	MatchSidesPositioning::MatchSidesPositioning(Location parent_side, Location object_side, float offset) : parent_side(parent_side), object_side(object_side), offset(offset) {
	}
	
	float MatchSidesPositioning::find_position(float parent_position, float object_size, float parent_size, float) {
		float position{parent_position + offset};
		switch(parent_side) {
			case Location::Origin:
				break;
			case Location::Center:
				position += parent_size * 0.5f;
				break;
			case Location::End:
				position += parent_size;
				break;
		}
		switch(object_side) {
			case Location::Origin:
				break;
			case Location::Center:
				position -= object_size * 0.5f;
				break;
			case Location::End:
				position -= object_size;
				break;
		}
		return position;
	}
	
	MatchSidesPositioning* MatchSidesPositioning::copy() {
		return new MatchSidesPositioning{*this};
	}
	
	bool DecodePointer<MatchSidesPositioning>::decode_pointer(const YAML::Node& node, MatchSidesPositioning*& match_sides_positioning) {
		match_sides_positioning = new MatchSidesPositioning{
			node["parent-side"].as<Location>(),
			node["object-side"].as<Location>(),
			conv_def(node["offset"], 0.f)
		};
		return true;
	}
}