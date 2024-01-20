#include "RelativeParentSizing.hpp"

namespace ie {
	RelativeParentSizing::Make::Make(float addition) : addition(addition) {
	}
	
	RelativeParentSizing* RelativeParentSizing::Make::make(float normal_size) {
		return new RelativeParentSizing{std::move(*this), normal_size};
	}
	
	RelativeParentSizing::RelativeParentSizing(Make&& make, float) :
		addition_(make.addition) {
	}
	
	RelativeParentSizing::RelativeParentSizing(float addition) : addition_(addition) {
	}
	
	void RelativeParentSizing::init(float) {
	}
	
	float RelativeParentSizing::find_size(float parent_size, float) {
		return parent_size + addition_;
	}
	
	float RelativeParentSizing::get_parent_size(float object_size) {
		return object_size - addition_;
	}
	
	RelativeParentSizing* RelativeParentSizing::copy() {
		return new RelativeParentSizing{*this};
	}
}

orl::Option<ie::RelativeParentSizing::Make> ieml::Decode<char, ie::RelativeParentSizing::Make>::decode(ieml::Node const& node) {
	return ie::RelativeParentSizing::Make{node.at("addition").except().as<float>().except()};
}