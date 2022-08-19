#pragma once
#include "../iWithCoefficientValue.hpp"
#include "../../reference/withReferenceValue.hpp"

namespace ui {
	class WithReferenceCoefficientValue : public IWithCoefficientValue, public WithReferenceValue<float> {
	public:
		explicit WithReferenceCoefficientValue(float& value);
		
		void setValue(const float& value) override;
		
		void setReference(float& valueReference) override;
	};
	
	typedef WithReferenceCoefficientValue WithRefCoefficient;
}
