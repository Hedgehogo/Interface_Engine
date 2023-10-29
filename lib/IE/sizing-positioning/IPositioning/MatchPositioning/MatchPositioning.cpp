#include "MatchPositioning.hpp"

namespace ie {
	MatchPositioning::MatchPositioning(float parent_coefficient, float object_coefficient, float offset) : parent_coefficient_(parent_coefficient), object_coefficient_(object_coefficient), offset_(offset) {
	}
	
	float MatchPositioning::find_position(float parent_position, float object_size, float parent_size, float) {
		return parent_position + parent_size * parent_coefficient_ - object_size * object_coefficient_ + offset_;
	}
	
	MatchPositioning* MatchPositioning::copy() {
		return new MatchPositioning{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<MatchPositioning>::decode_pointer(const YAML::Node& node, MatchPositioning*& match_positioning) {
		match_positioning = new MatchPositioning{
			node["parent-coefficient"].as<float>(),
			node["object-coefficient"].as<float>(),
			conv_def(node["offset"], 0.f)
		};
		return true;

	}
	*/
}