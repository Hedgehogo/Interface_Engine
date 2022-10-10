#pragma once
#include "../iWithCoefficientValue.hpp"
#include "../../general/withValue.hpp"

namespace ui {
	class WithCoefficientValue : public WithValue<float>, public IWithCoefficientValue {
	public:
		explicit WithCoefficientValue(float value = 0.f);
		
		void setValue(const float& value) override;
	};
	
	bool convertPointer(const YAML::Node &node, WithCoefficientValue *&withCoefficientValue);
	
	typedef WithCoefficientValue WithCoefficient;
}
