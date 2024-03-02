#include "RelativeParentSizing.hpp"

namespace ie {
	RelativeParentSizing::Make::Make(float addition) : addition(addition) {
	}
	
	auto RelativeParentSizing::Make::make(float normal_size) -> RelativeParentSizing* {
		return new RelativeParentSizing{std::move(*this), normal_size};
	}
	
	RelativeParentSizing::RelativeParentSizing(Make&& make, float) :
		addition_(make.addition) {
	}
	
	RelativeParentSizing::RelativeParentSizing(float addition) : addition_(addition) {
	}
	
	auto RelativeParentSizing::find_size(float parent_size, float) -> float {
		return parent_size + addition_;
	}
	
	auto RelativeParentSizing::get_parent_size(float object_size) -> float {
		return object_size - addition_;
	}
}

auto ieml::Decode<char, ie::RelativeParentSizing::Make>::decode(ieml::Node const& node) -> orl::Option<ie::RelativeParentSizing::Make> {
	return ie::RelativeParentSizing::Make{node.at("addition").except().as<float>().except()};
}