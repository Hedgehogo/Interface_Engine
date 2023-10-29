#pragma once

#include "../BaseSConvertToBoolComparison.hpp"
#include "../../../../../buffer/Buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolGreater : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T from_value, T compared) override;
	
	public:
		SConvertToBoolGreater(PISValue<T> from_value, T compared);
	};
	
	/*old_yaml_decode_pointer
	template<typename T>
	struct DecodePointer<SConvertToBoolGreater<T> > {
		static bool decode_pointer(const YAML::Node& node, SConvertToBoolGreater<T>*& sConvert_to_bool_greater);
	};
	*/
	
	using SConvertFloatToBoolGreater = SConvertToBoolGreater<float>;
	using SConvertIntToBoolGreater = SConvertToBoolGreater<int>;
}

#include "SConvertToBoolGreater.inl"