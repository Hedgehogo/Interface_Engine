#pragma once

#include "../../SRangeValue/SRangeValue.hpp"

namespace ie {
	template<typename T>
	class SConvertRange : public SRangeValue<T> {
	public:
		explicit SConvertRange(PSRange<T> sRangeValue, T upper, T lower);
	
	protected:
		PSRange<T> sRangeValue;
	};
	
	template<typename T>
	struct DecodePointer<SConvertRange<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertRange<T>*& sConvertRange);
	};
	
	using SCRint = SConvertRange<int>;
	using SCRfloat = SConvertRange<float>;
}

#include "SConvertRange.inl"