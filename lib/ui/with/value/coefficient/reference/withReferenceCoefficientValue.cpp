#include "withReferenceCoefficientValue.hpp"
#include <algorithm>

namespace ui {
	WithReferenceCoefficientValue::WithReferenceCoefficientValue(float &value) : WithReferenceValue(value) {}
	
	void WithReferenceCoefficientValue::setValue(const float &value) {
		*this->valueReference = std::min(std::max(value, 0.f), 1.f);
	}
	
	void WithReferenceCoefficientValue::setReference(float &valueReference) {
		this->valueReference = &valueReference;
		setValue(valueReference);
	}
}