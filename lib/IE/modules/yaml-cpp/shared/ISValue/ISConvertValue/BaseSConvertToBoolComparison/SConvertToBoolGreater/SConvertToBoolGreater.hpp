#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolGreater : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T fromValue, T compared) override;
	
	public:
		SConvertToBoolGreater(PISValue<T> fromValue, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolGreater<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertToBoolGreater<T>*& sConvertToBoolGreater);
	};
	
	using SConvertFloatToBoolGreater = SConvertToBoolGreater<float>;
	using SConvertIntToBoolGreater = SConvertToBoolGreater<int>;
}

#include "SConvertToBoolGreater.inl"