#pragma once

#include "../iSCoefficientValue.hpp"
#include "../../reference/sReferenceValue.hpp"

namespace ui {
	class SReferenceCoefficientValue : public ISCoefficientValue, public SReferenceValue<float> {
	public:
		explicit SReferenceCoefficientValue(float& value);
		
		void setValue(const float& value) override;
		
		void setReference(float& valueReference) override;
	};
	
	typedef SReferenceCoefficientValue SRefCoefficient;
	
	typedef std::shared_ptr<SRefCoefficient> PSRefCoefficient;
}
