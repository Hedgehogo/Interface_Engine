#include "ConstSizing.hpp"

namespace ie {
	ConstSizing::Make::Make(float size) : size(size) {
	}
	
	ConstSizing* ConstSizing::Make::make(float normal_size) {
		return new ConstSizing{std::move(*this), normal_size};
	}
	
	ConstSizing::ConstSizing(Make&& make, float) : size_(make.size) {
	}
	
	ConstSizing::ConstSizing(float size) : size_(size) {
	}
	
	void ConstSizing::init(float) {
	}
	
	float ConstSizing::find_size(float, float) {
		return this->size_;
	}
	
	ConstSizing* ConstSizing::copy() {
		return new ConstSizing{*this};
	}
}

orl::Option<ie::ConstSizing::Make> ieml::Decode<char, ie::ConstSizing::Make>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if(auto scalar{clear_node.as<float>()}) {
		return {{scalar.ok()}};
	}
	return {{clear_node.at("size").except().as<float>().except()}};
}