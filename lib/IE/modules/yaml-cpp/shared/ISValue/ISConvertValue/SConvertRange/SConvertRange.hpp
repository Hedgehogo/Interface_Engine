#pragma once

#include "../../SRangeValue/SRangeValue.hpp"

namespace ie {
	template<typename T>
	class SConvertRange : public SRangeValue<T> {
	public:
		explicit SConvertRange(PSRange<T> value, T upper, T lower);
	
	protected:
		PSRange<T> value_;
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SConvertRange<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertRange<T>*& sConvert_range);
	};
	*/
	
	using SCRint = SConvertRange<int>;
	using SCRfloat = SConvertRange<float>;
}

#include "SConvertRange.inl"