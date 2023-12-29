#pragma once

#include "../ISCoefficientValue.hpp"
#include "../../SReferenceValue/SReferenceValue.hpp"

namespace ie {
	class SReferenceCoefficientValue : public SReferenceValue<float>, public virtual ISCoefficientValue {
	public:
		explicit SReferenceCoefficientValue(float& value);
		
		void set_value(const float& value) override;
		
		void set_reference(float& value_reference) override;
	};
	
	using SRefCoefficient = SReferenceCoefficientValue;
	
	using PSRefCoefficient = std::shared_ptr<SRefCoefficient>;
}
