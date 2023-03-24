#pragma once

#include "../baseComparison/baseSConvertToBoolComparison.hpp"
#include "modules/appendix/yaml-cpp/buffer/buffer.hpp"

namespace ui {
	template<typename T>
	class SConvertToBoolGreater : public BaseSConvertToBoolComparison<T>{
	protected:
		bool convert(T fromValue, T compared) override;

	public:
		SConvertToBoolGreater(PISValue<T> fromValue, T compared);
	};

	template<typename T>
	bool convertPointer(const YAML::Node &node,  SConvertToBoolGreater<T> *&sConvertToBoolGreater);

	using SConvertFloatToBoolGreater = SConvertToBoolGreater<float>;
	using SConvertIntToBoolGreater = SConvertToBoolGreater<int>;
}

#include "sConvertToBoolGreater.inl"