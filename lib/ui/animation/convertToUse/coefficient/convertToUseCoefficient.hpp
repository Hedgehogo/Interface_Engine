#pragma once

#include "../iConvertToUse.hpp"

namespace ui {
	template<typename T>
	class ConvertToUseCoefficient : public IConvertToUse<T>{
	protected:
		float coefficient;

		T convert(float value) override;

	public:
		explicit ConvertToUseCoefficient(float coefficient);
	};
}

#include "convertToUseCoefficient.inl"