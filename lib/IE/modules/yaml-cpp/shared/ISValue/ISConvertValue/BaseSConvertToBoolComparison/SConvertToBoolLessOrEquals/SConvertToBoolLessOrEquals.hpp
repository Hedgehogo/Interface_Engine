#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolLessOrEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T fromValue, T compared) override;
	
	public:
		SConvertToBoolLessOrEquals(PISValue<T> fromValue, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolLessOrEquals<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertToBoolLessOrEquals<T>*& sConvertToBoolLessOrEquals);
	};
	
	using SConvertFloatToBoolLessOrEquals = SConvertToBoolLessOrEquals<float>;
	using SConvertIntToBoolLessOrEquals = SConvertToBoolLessOrEquals<int>;
}

#include "SConvertToBoolLessOrEquals.inl"