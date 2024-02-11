#include "InternalPositioning.hpp"

namespace ie {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient_(coefficient), offset_(offset) {
	}
	
	float InternalPositioning::find_position(float parent_position, float object_size, float parent_size, float) {
		return parent_position + (parent_size - object_size) * coefficient_ + offset_;
	}
	
	InternalPositioning* InternalPositioning::copy() {
		return new InternalPositioning{*this};
	}
	
	float InternalPositioning::get_coefficient() const {
		return coefficient_;
	}
	
	float InternalPositioning::get_offset() const {
		return offset_;
	}
}

orl::Option<ie::InternalPositioning> ieml::Decode<char, ie::InternalPositioning>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	for(auto result: clear_node.as<float>().ok_or_none()) {
		return ie::InternalPositioning{result};
	}
	auto map{clear_node.get_map_view().except()};
	return ie::InternalPositioning{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("offset").ok_or(0.),
	};
}
