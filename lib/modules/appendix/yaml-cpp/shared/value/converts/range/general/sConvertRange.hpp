#pragma once

#include "../../../range/sRangeValue.hpp"

namespace ui{
	template<typename T>
	class SConvertRange : public SRangeValue<T>{
	protected:
		PSRange<T> sRangeValue;
		
	public:
		explicit SConvertRange(PSRange<T> sRangeValue, T upper, T lower);
	};
	
	
	template<typename T>
	struct DecodePointer<SConvertRange<T>> {
		static bool decodePointer(const YAML::Node& node, SConvertRange<T>*& sConvertRange);
	};
	
	using SCRint = SConvertRange<int>;
	using SCRfloat = SConvertRange<float>;
}

#include "sConvertRange.inl"