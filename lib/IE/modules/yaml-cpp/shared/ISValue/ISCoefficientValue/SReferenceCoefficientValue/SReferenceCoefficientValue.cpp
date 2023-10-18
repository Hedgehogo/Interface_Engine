#include "SReferenceCoefficientValue.hpp"
#include <algorithm>

namespace ie {
	SReferenceCoefficientValue::SReferenceCoefficientValue(float& value) : SReferenceValue(value) {
	}
	
	void SReferenceCoefficientValue::set_value(const float& value) {
		*this->value_reference = std::min(std::max(value, 0.f), 1.f);
		for(const auto& set: setters)
			set(*this->value_reference);
	}
	
	void SReferenceCoefficientValue::set_reference(float& value_reference) {
		this->value_reference = &value_reference;
		set_value(value_reference);
	}
}