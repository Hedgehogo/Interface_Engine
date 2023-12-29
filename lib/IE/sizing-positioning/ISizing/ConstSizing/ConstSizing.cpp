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
	
	bool DecodePointer<ConstSizing>::decode_pointer(const YAML::Node& node, ConstSizing*& const_sizing) {
		if(node.IsScalar()) {
			const_sizing = new ConstSizing{node.as<float>()};
		} else {
			const_sizing = new ConstSizing{node["size"].as<float>()};
		}
		return true;
	}
}