#include "constSizing.hpp"

namespace ui {
	ConstSizing::ConstSizing(float size) : size(size) {
	}
	
	void ConstSizing::init(float) {
	}
	
	float ConstSizing::findSize(float, float) {
		return this->size;
	}
	
	ConstSizing* ConstSizing::copy() {
		return new ConstSizing(size);
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