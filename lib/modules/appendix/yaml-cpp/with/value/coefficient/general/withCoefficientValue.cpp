#include "withCoefficientValue.hpp"
#include <algorithm>

namespace ui {
	WithCoefficientValue::WithCoefficientValue(float value) : WithValue(std::min(std::max(value, 0.f), 1.f)) {}
	
	void WithCoefficientValue::setValue(const float &value) {
		this->value = std::min(std::max(value, 0.f), 1.f);
	}
	
	bool convertPointer(const YAML::Node &node, WithCoefficientValue *&withCoefficientValue) {
		float value{0.f};
		
		if(node["value"])
			node["value"] >> value;
		
		{ withCoefficientValue = new WithCoefficientValue{value}; return true; }
	}
}
