#include "MatchSidesPositioning.hpp"

namespace ie {
	MatchSidesPositioning::MatchSidesPositioning(Location parent_side, Location object_side, float offset) :
		parent_side_(parent_side), object_side_(object_side), offset_(offset) {
	}
	
	auto MatchSidesPositioning::find_position(float parent_position, float object_size, float parent_size, float) -> float {
		float position{parent_position + offset_};
		switch(parent_side_) {
			case Location::Origin:
				break;
			case Location::Center:
				position += parent_size * 0.5f;
				break;
			case Location::End:
				position += parent_size;
				break;
		}
		switch(object_side_) {
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
	
	auto MatchSidesPositioning::copy() -> MatchSidesPositioning* {
		return new MatchSidesPositioning{*this};
	}
}

auto ieml::Decode<char, ie::MatchSidesPositioning>::decode(ieml::Node const& node) -> orl::Option<ie::MatchSidesPositioning> {
	auto map{node.get_map_view().except()};
	return ie::MatchSidesPositioning{
		map.at("parent-side").except().as<ie::Location>().except(),
		map.at("object-side").except().as<ie::Location>().except(),
		map.get_as<float>("offset").except().ok_or(0.),
	};
}
