#include "MatchTargetPositioning.hpp"

namespace ie {
	MatchTargetPositioning::MatchTargetPositioning(float target_coefficient, float object_coefficient, float offset) :
		target_coefficient_(target_coefficient), object_coefficient_(object_coefficient), offset_(offset) {
	}
	
	float MatchTargetPositioning::find_position(float, float object_size, float, float target_size) {
		return target_size * target_coefficient_ - object_size * object_coefficient_ + offset_;
	}
	
	MatchTargetPositioning* MatchTargetPositioning::copy() {
		return new MatchTargetPositioning{*this};
	}
}

orl::Option<ie::MatchTargetPositioning> ieml::Decode<char, ie::MatchTargetPositioning>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::MatchTargetPositioning{
		map.at("target-coefficient").except().as<float>().except(),
		map.at("object-coefficient").except().as<float>().except(),
		map.get_as<float>("offset").ok_or(0.),
	};
}
