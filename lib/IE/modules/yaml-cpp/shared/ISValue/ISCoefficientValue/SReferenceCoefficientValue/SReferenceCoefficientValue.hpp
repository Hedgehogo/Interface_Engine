#pragma once

#include "../ISCoefficientValue.hpp"
#include "../../SReferenceValue/SReferenceValue.hpp"

namespace ie {
	class SReferenceCoefficientValue : public SReferenceValue<float>, public virtual ISCoefficientValue {
	public:
		explicit SReferenceCoefficientValue(float& value);
		
		void setValue(const float& value) override;
		
		void setReference(float& valueReference) override;
	};
	
	typedef SReferenceCoefficientValue SRefCoefficient;
	
	typedef std::shared_ptr<SRefCoefficient> PSRefCoefficient;
}
