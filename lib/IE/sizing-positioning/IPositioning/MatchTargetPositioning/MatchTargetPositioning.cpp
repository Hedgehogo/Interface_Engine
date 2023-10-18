#include "MatchTargetPositioning.hpp"

namespace ie {
	MatchTargetPositioning::MatchTargetPositioning(float target_coefficient, float object_coefficient, float offset) : target_coefficient(target_coefficient), object_coefficient(object_coefficient), offset(offset) {
	}
	
	float MatchTargetPositioning::find_position(float, float object_size, float, float target_size) {
		return target_size * target_coefficient - object_size * object_coefficient + offset;
	}
	
	MatchTargetPositioning* MatchTargetPositioning::copy() {
		return new MatchTargetPositioning{*this};
	}
	
	bool DecodePointer<MatchTargetPositioning>::decode_pointer(const YAML::Node& node, MatchTargetPositioning*& match_target_positioning) {
		match_target_positioning = new MatchTargetPositioning{
			node["target-coefficient"].as<float>(),
			node["object-coefficient"].as<float>(),
			conv_def(node["offset"], 0.f)
		};
		return true;
	}
}