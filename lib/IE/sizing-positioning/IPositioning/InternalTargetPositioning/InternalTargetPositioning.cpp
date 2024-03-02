#include "InternalTargetPositioning.hpp"

namespace ie {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient_(coefficient), offset_(offset) {
	}
	
	auto InternalTargetPositioning::find_position(float, float object_size, float, float target_size) -> float {
		return (target_size - object_size) * coefficient_ + offset_;
	}
	
	auto InternalTargetPositioning::copy() -> InternalTargetPositioning* {
		return new InternalTargetPositioning{*this};
	}
	
	auto InternalTargetPositioning::get_coefficient() const -> float {
		return coefficient_;
	}
	
	auto InternalTargetPositioning::get_offset() const -> float {
		return offset_;
	}
}

auto ieml::Decode<char, ie::InternalTargetPositioning>::decode(ieml::Node const& node) -> orl::Option<ie::InternalTargetPositioning> {
	auto map{node.get_map_view().except()};
	return ie::InternalTargetPositioning{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("offset").except().ok_or(0.)
	};
}
