#include "RelativeNormalSizing.hpp"

namespace ie {
	RelativeNormalSizing* RelativeNormalSizing::Make::make(float normal_size) {
		return new RelativeNormalSizing{std::move(*this), normal_size};
	}
	
	RelativeNormalSizing::RelativeNormalSizing(Make&&, float normal_size) :
		normal_size_(normal_size) {
	}
	
	RelativeNormalSizing::RelativeNormalSizing() : normal_size_(0) {
	}
	
	float RelativeNormalSizing::find_size(float, float) {
		return this->normal_size_;
	}
}

orl::Option<ie::RelativeNormalSizing::Make> ieml::Decode<char, ie::RelativeNormalSizing::Make>::decode(ieml::Node const&) {
	return {{}};
}
