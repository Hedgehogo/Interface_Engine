#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolLess : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T from_value, T compared) override;
	
	public:
		SConvertToBoolLess(PISValue<T> from_value, T compared);
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SConvertToBoolLess<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertToBoolLess<T>*& sConvert_to_bool_greater);
	};
	*/
	
	using SConvertFloatToBoolLess = SConvertToBoolLess<float>;
	using SConvertIntToBoolLess = SConvertToBoolLess<int>;
}

#include "SConvertToBoolLess.inl"