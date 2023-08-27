#include "ConstSizing.hpp"

namespace ie {
	ConstSizing::Make::Make(float size) : size(size) {
	}
	
	ConstSizing* ConstSizing::Make::make(float normalSize) {
		return new ConstSizing{std::move(*this), normalSize};
	}
	
	ConstSizing::ConstSizing(Make&& make, float) : size(make.size) {
	}
	
	ConstSizing::ConstSizing(float size) : size(size) {
	}
	
	void ConstSizing::init(float) {
	}
	
	float ConstSizing::findSize(float, float) {
		return this->size;
	}
	
	ConstSizing* ConstSizing::copy() {
		return new ConstSizing{*this};
	}
	
	bool DecodePointer<ConstSizing>::decodePointer(const YAML::Node& node, ConstSizing*& constSizing) {
		if(node.IsScalar()) {
			constSizing = new ConstSizing{node.as<float>()};
		} else {
			constSizing = new ConstSizing{node["size"].as<float>()};
		}
		return true;
	}
}