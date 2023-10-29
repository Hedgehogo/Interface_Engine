#pragma once

#include "../ISCoefficientValue.hpp"
#include "../../SValue/SValue.hpp"

namespace ie {
	////////////////////////////////////////////////////////////
	/// \brief Shared variable intended for values from 0 to 1.
	///
	/// \deprecated The class is weakly extensible and narrowly focused.
	/// 			Use SRangeValue instead.
	///
	////////////////////////////////////////////////////////////
	class SCoefficientValue : public SValue<float>, public virtual ISCoefficientValue {
	public:
		explicit SCoefficientValue(float value = 0.f);
		
		void set_value(const float& value) override;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<SCoefficientValue> {
		static bool decode_pointer(const YAML::Node& node, SCoefficientValue*& sCoefficient_value);
	};
	*/
	
	using SCoefficient = SCoefficientValue;
	
	using PSCoefficient = std::shared_ptr<SCoefficient>;
}
