#pragma once
#include "../iSCoefficientValue.hpp"
#include "../../general/withValue.hpp"

namespace ui {
	class SCoefficientValue : public SValue<float>, public ISCoefficientValue {
	public:
		explicit SCoefficientValue(float value = 0.f);
		
		void setValue(const float& value) override;
	};
	
	bool convertPointer(const YAML::Node &node, SCoefficientValue *&sCoefficientValue);
	
	typedef SCoefficientValue SCoefficient;
	
	typedef std::shared_ptr<SCoefficient> PSCoefficient;
}
