#include "InternalTargetPositioning.hpp"

namespace ie {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient_(coefficient), offset_(offset) {
	}
	
	float InternalTargetPositioning::find_position(float, float object_size, float, float target_size) {
		return (target_size - object_size) * coefficient_ + offset_;
	}
	
	InternalTargetPositioning* InternalTargetPositioning::copy() {
		return new InternalTargetPositioning{*this};
	}
	
	float InternalTargetPositioning::get_coefficient() const {
		return coefficient_;
	}
	
	float InternalTargetPositioning::get_offset() const {
		return offset_;
	}
	
	bool DecodePointer<InternalTargetPositioning>::decode_pointer(const YAML::Node& node, InternalTargetPositioning*& internal_target_positioning) {
		internal_target_positioning = new InternalTargetPositioning{
			node["coefficient"].as<float>(),
			conv_def(node["offset"], 0.f)
		};
		return true;
	}
}