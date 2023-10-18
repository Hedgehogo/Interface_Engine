#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolGreaterOrEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T from_value, T compared) override;
	
	public:
		SConvertToBoolGreaterOrEquals(PISValue<T> from_value, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolGreaterOrEquals<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertToBoolGreaterOrEquals<T>*& sConvert_to_bool_greater_or_equals);
	};
	
	using SConvertFloatToBoolGreaterOrEquals = SConvertToBoolGreaterOrEquals<float>;
	using SConvertIntToBoolGreaterOrEquals = SConvertToBoolGreaterOrEquals<int>;
}

#include "SConvertToBoolGreaterOrEquals.inl"