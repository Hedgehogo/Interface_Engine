#include "MatchTargetPositioning.hpp"

namespace ie {
	MatchTargetPositioning::MatchTargetPositioning(float target_coefficient, float object_coefficient, float offset) :
		target_coefficient_(target_coefficient), object_coefficient_(object_coefficient), offset_(offset) {
	}
	
	auto MatchTargetPositioning::find_position(float, float object_size, float, float target_size) -> float {
		return target_size * target_coefficient_ - object_size * object_coefficient_ + offset_;
	}
	
	auto MatchTargetPositioning::copy() -> MatchTargetPositioning* {
		return new MatchTargetPositioning{*this};
	}
}

auto ieml::Decode<char, ie::MatchTargetPositioning>::decode(ieml::Node const& node) -> orl::Option<ie::MatchTargetPositioning> {
	auto map{node.get_map_view().except()};
	return ie::MatchTargetPositioning{
		map.at("target-coefficient").except().as<float>().except(),
		map.at("object-coefficient").except().as<float>().except(),
		map.get_as<float>("offset").except().ok_or(0.),
	};
}
