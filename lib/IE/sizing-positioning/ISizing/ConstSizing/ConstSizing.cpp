#include "ConstSizing.hpp"

namespace ie {
	ConstSizing::Make::Make(float size) : size(size) {
	}
	
	auto ConstSizing::Make::make(float normal_size) -> ConstSizing* {
		return new ConstSizing{std::move(*this), normal_size};
	}
	
	ConstSizing::ConstSizing(Make&& make, float) : size_(make.size) {
	}
	
	ConstSizing::ConstSizing(float size) : size_(size) {
	}
	
	auto ConstSizing::find_size(float, float) -> float {
		return this->size_;
	}
}

auto ieml::Decode<char, ie::ConstSizing::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ConstSizing::Make> {
	auto& clear_node{node.get_clear()};
	for(auto scalar: clear_node.as<float>().ok_or_none()) {
		return {{scalar}};
	}
	return {{clear_node.at("size").except().as<float>().except()}};
}