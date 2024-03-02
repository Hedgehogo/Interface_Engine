#include "InternalPositioning.hpp"

namespace ie {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient_(coefficient), offset_(offset) {
	}
	
	auto InternalPositioning::find_position(float parent_position, float object_size, float parent_size, float) -> float {
		return parent_position + (parent_size - object_size) * coefficient_ + offset_;
	}
	
	auto InternalPositioning::copy() -> InternalPositioning* {
		return new InternalPositioning{*this};
	}
	
	auto InternalPositioning::get_coefficient() const -> float {
		return coefficient_;
	}
	
	auto InternalPositioning::get_offset() const -> float {
		return offset_;
	}
}

auto ieml::Decode<char, ie::InternalPositioning>::decode(ieml::Node const& node) -> orl::Option<ie::InternalPositioning> {
	auto& clear_node{node.get_clear()};
	for(auto result: clear_node.as<float>().ok_or_none()) {
		return ie::InternalPositioning{result};
	}
	auto map{clear_node.get_map_view().except()};
	return ie::InternalPositioning{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("offset").except().ok_or(0.),
	};
}
