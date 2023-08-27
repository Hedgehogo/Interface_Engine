#include "sReferenceCoefficientValue.hpp"
#include <algorithm>

namespace ie {
	SReferenceCoefficientValue::SReferenceCoefficientValue(float& value) : SReferenceValue(value) {
	}
	
	void SReferenceCoefficientValue::setValue(const float& value) {
		*this->valueReference = std::min(std::max(value, 0.f), 1.f);
		for(const auto& set: setters)
			set(*this->valueReference);
	}
	
	void SReferenceCoefficientValue::setReference(float& valueReference) {
		this->valueReference = &valueReference;
		setValue(valueReference);
	}
}