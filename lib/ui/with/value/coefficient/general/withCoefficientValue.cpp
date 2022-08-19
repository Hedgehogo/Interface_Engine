#include "withCoefficientValue.hpp"
#include <algorithm>

namespace ui {
	WithCoefficientValue::WithCoefficientValue(float value) : WithValue(value) {}
	
	void WithCoefficientValue::setValue(const float &value) {
		this->value = std::min(std::max(value, 0.f), 1.f);
	}
}
