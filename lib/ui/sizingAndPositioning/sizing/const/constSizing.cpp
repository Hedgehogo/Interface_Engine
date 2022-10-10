#include "constSizing.hpp"

namespace ui {
	ConstSizing::ConstSizing(float size) : size(size) {}
	
	void ConstSizing::init(float) {}
	
	float ConstSizing::findSize(float, float) {
		return this->size;
	}
	
	ConstSizing *ConstSizing::copy() {
		return new ConstSizing(size);
	}
	
	bool convertPointer(const YAML::Node &node, ConstSizing *&constSizing) {
		float size;
		node["size"] >> size;
		{ constSizing = new ConstSizing{size}; return true; }
	}
	
	Sizing *size(float constSize) {
		return new ConstSizing{constSize};
	}
}