#include "RelativeNormalSizing.hpp"

namespace ie {
	auto RelativeNormalSizing::Make::make(float normal_size) -> RelativeNormalSizing* {
		return new RelativeNormalSizing{std::move(*this), normal_size};
	}
	
	RelativeNormalSizing::RelativeNormalSizing(Make&&, float normal_size) :
		normal_size_(normal_size) {
	}
	
	RelativeNormalSizing::RelativeNormalSizing() : normal_size_(0) {
	}
	
	auto RelativeNormalSizing::find_size(float, float) -> float {
		return this->normal_size_;
	}
}

auto ieml::Decode<char, ie::RelativeNormalSizing::Make>::decode(ieml::Node const&) -> orl::Option<ie::RelativeNormalSizing::Make> {
	return {{}};
}
