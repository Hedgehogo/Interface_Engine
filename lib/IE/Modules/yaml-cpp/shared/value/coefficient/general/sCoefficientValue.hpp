#pragma once

#include "../iSCoefficientValue.hpp"
#include "../../general/sValue.hpp"

namespace ie {
	////////////////////////////////////////////////////////////
	/// \brief Shared variable intended for values from 0 to 1.
	///
	/// \deprecated The class is weakly extensible and narrowly focused.
	/// 			Use SRangeValue instead.
	///
	////////////////////////////////////////////////////////////
	class SCoefficientValue : public SValue<float>, public ISCoefficientValue {
	public:
		explicit SCoefficientValue(float value = 0.f);
		
		void setValue(const float& value) override;
	};
	
	template<>
	struct DecodePointer<SCoefficientValue> {
		static bool decodePointer(const YAML::Node& node, SCoefficientValue*& sCoefficientValue);
	};
	
	typedef SCoefficientValue SCoefficient;
	
	typedef std::shared_ptr<SCoefficient> PSCoefficient;
}
