#include "SCoefficientValue.hpp"
#include <algorithm>

namespace ie {
	SCoefficientValue::SCoefficientValue(float value) : SValue(std::min(std::max(value, 0.f), 1.f)) {
	}
	
	void SCoefficientValue::set_value(const float& value) {
		this->value = std::min(std::max(value, 0.f), 1.f);
		for(const auto& set: setters)
			set(this->value);
	}
	
	bool DecodePointer<SCoefficientValue>::decode_pointer(const YAML::Node& node, SCoefficientValue*& sCoefficient_value) {
		sCoefficient_value = new SCoefficientValue{conv_def(node["value"], 0.f)};
		return true;
	}
}
