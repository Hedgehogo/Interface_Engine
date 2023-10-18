#include "RelativeNormalSizing.hpp"

namespace ie {
	RelativeNormalSizing* RelativeNormalSizing::Make::make(float normal_size) {
		return new RelativeNormalSizing{std::move(*this), normal_size};
	}
	
	RelativeNormalSizing::RelativeNormalSizing(Make&&, float normal_size) :
		normal_size(normal_size) {
	}
	
	RelativeNormalSizing::RelativeNormalSizing() : normal_size(0) {
	}
	
	void RelativeNormalSizing::init(float normal_size) {
		this->normal_size = normal_size;
	}
	
	float RelativeNormalSizing::find_size(float, float) {
		return this->normal_size;
	}
	
	RelativeNormalSizing* RelativeNormalSizing::copy() {
		return new RelativeNormalSizing{*this};
	}
	
	bool DecodePointer<RelativeNormalSizing>::decode_pointer(const YAML::Node&, RelativeNormalSizing*& relative_normal_sizing) {
		relative_normal_sizing = new RelativeNormalSizing{};
		return true;
	}
}