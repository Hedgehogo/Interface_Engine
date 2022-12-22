#pragma once

#include "../coefficient/convertToUseCoefficient.hpp"

namespace ui {
	template<typename T>
	class ConvertToUseCoefficientWithRange : public ConvertToUseCoefficient<T>{
		float max, min;

		T convert(float value) override;

	public:
		ConvertToUseCoefficientWithRange(float coefficient = 1, float max = 1, float min = 0);
    };
}

#include "convertToUseCoefficientWithRange.inl"