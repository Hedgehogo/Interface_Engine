#include "MatchPositioning.hpp"

namespace ie {
	MatchPositioning::MatchPositioning(float parent_coefficient, float object_coefficient, float offset) : parent_coefficient(parent_coefficient), object_coefficient(object_coefficient), offset(offset) {
	}
	
	float MatchPositioning::find_position(float parent_position, float object_size, float parent_size, float) {
		return parent_position + parent_size * parent_coefficient - object_size * object_coefficient + offset;
	}
	
	MatchPositioning* MatchPositioning::copy() {
		return new MatchPositioning{*this};
	}
	
	bool DecodePointer<MatchPositioning>::decode_pointer(const YAML::Node& node, MatchPositioning*& match_positioning) {
		match_positioning = new MatchPositioning{
			node["parent-coefficient"].as<float>(),
			node["object-coefficient"].as<float>(),
			conv_def(node["offset"], 0.f)
		};
		return true;
	}
}