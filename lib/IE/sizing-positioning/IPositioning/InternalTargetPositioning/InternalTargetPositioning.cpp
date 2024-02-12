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
}

orl::Option<ie::InternalTargetPositioning> ieml::Decode<char, ie::InternalTargetPositioning>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::InternalTargetPositioning{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("offset").except().ok_or(0.)
	};
}
