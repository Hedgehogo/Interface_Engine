#pragma once

#include "../baseComparison/baseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolLess : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T fromValue, T compared) override;
	
	public:
		SConvertToBoolLess(PISValue<T> fromValue, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolLess<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertToBoolLess<T>*& sConvertToBoolGreater);
	};
	
	using SConvertFloatToBoolLess = SConvertToBoolLess<float>;
	using SConvertIntToBoolLess = SConvertToBoolLess<int>;
}

#include "sConvertToBoolLess.inl"