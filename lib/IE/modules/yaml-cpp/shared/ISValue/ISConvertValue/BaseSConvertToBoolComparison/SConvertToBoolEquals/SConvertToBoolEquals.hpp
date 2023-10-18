#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T from_value, T compared) override;
	
	public:
		SConvertToBoolEquals(PISValue<T> from_value, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolEquals<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertToBoolEquals<T>*& sConvert_to_bool_equals);
	};
	
	using SConvertFloatToBoolEquals = SConvertToBoolEquals<float>;
	using SConvertIntToBoolEquals = SConvertToBoolEquals<int>;
}

#include "SConvertToBoolEquals.inl"