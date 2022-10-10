#include "sReferenceCoefficientValue.hpp"
#include <algorithm>

namespace ui {
	SReferenceCoefficientValue::SReferenceCoefficientValue(float &value) : SReferenceValue(value) {}
	
	void SReferenceCoefficientValue::setValue(const float &value) {
		*this->valueReference = std::min(std::max(value, 0.f), 1.f);
	}
	
	void SReferenceCoefficientValue::setReference(float &valueReference) {
		this->valueReference = &valueReference;
		setValue(valueReference);
	}
}