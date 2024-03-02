#include "MatchPositioning.hpp"

namespace ie {
	MatchPositioning::MatchPositioning(float parent_coefficient, float object_coefficient, float offset) : parent_coefficient_(parent_coefficient), object_coefficient_(object_coefficient), offset_(offset) {
	}
	
	auto MatchPositioning::find_position(float parent_position, float object_size, float parent_size, float) -> float {
		return parent_position + parent_size * parent_coefficient_ - object_size * object_coefficient_ + offset_;
	}
	
	auto MatchPositioning::copy() -> MatchPositioning* {
		return new MatchPositioning{*this};
	}
}

auto ieml::Decode<char, ie::MatchPositioning>::decode(ieml::Node const& node) -> orl::Option<ie::MatchPositioning> {
	auto map{node.get_map_view().except()};
	return ie::MatchPositioning{
		map.at("parent-coefficient").except().as<float>().except(),
		map.at("object-coefficient").except().as<float>().except(),
		map.get_as<float>("offset").except().ok_or(0.),
	};
}