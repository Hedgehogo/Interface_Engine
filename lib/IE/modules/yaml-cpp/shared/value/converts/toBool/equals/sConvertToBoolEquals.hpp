#pragma once

#include "../baseComparison/baseSConvertToBoolComparison.hpp"
#include "IE/Modules/yaml-cpp/buffer/buffer.hpp"

namespace ie {
	template<typename T>
	class SConvertToBoolEquals : public BaseSConvertToBoolComparison<T> {
	protected:
		bool convert(T fromValue, T compared) override;
	
	public:
		SConvertToBoolEquals(PISValue<T> fromValue, T compared);
	};
	
	template<typename T>
	struct DecodePointer<SConvertToBoolEquals<T> > {
		static bool decodePointer(const YAML::Node& node, SConvertToBoolEquals<T>*& sConvertToBoolEquals);
	};
	
	using SConvertFloatToBoolEquals = SConvertToBoolEquals<float>;
	using SConvertIntToBoolEquals = SConvertToBoolEquals<int>;
}

#include "sConvertToBoolEquals.inl"