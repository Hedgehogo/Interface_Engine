#include "sCoefficientValue.hpp"
#include <algorithm>

namespace ui {
	SCoefficientValue::SCoefficientValue(float value) : SValue(std::min(std::max(value, 0.f), 1.f)) {}
	
	void SCoefficientValue::setValue(const float &value) {
		this->value = std::min(std::max(value, 0.f), 1.f);
		for(const auto &set: setters) set(this->value);
	}
	
	bool convertPointer(const YAML::Node &node, SCoefficientValue *&sCoefficientValue) {
		float value{0.f};
		
		if(node["value"])
			node["value"] >> value;
		
		{ sCoefficientValue = new SCoefficientValue{value}; return true; }
	}
}
