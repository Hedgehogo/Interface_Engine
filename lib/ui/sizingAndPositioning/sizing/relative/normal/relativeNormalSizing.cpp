#include "relativeNormalSizing.hpp"

namespace ui {
	RelativeNormalSizing::RelativeNormalSizing() : normalSize(0) {
	}
	
	void RelativeNormalSizing::init(float normalSize) {
		this->normalSize = normalSize;
	}
	
	float RelativeNormalSizing::findSize(float, float) {
		return this->normalSize;
	}
	
	RelativeNormalSizing* RelativeNormalSizing::copy() {
		return new RelativeNormalSizing{*this};
	}
	
	bool DecodePointer<RelativeNormalSizing>::decodePointer(const YAML::Node&, RelativeNormalSizing*& relativeNormalSizing) {
		relativeNormalSizing = new RelativeNormalSizing{};
		return true;
	}
}