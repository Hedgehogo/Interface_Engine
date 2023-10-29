#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolLessOrEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T from_value, T compared) override;
	
	public:
		SConvertToBoolLessOrEquals(PISValue<T> from_value, T compared);
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SConvertToBoolLessOrEquals<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertToBoolLessOrEquals<T>*& sConvert_to_bool_less_or_equals);
	};
	*/
	
	using SConvertFloatToBoolLessOrEquals = SConvertToBoolLessOrEquals<float>;
	using SConvertIntToBoolLessOrEquals = SConvertToBoolLessOrEquals<int>;
}

#include "SConvertToBoolLessOrEquals.inl"