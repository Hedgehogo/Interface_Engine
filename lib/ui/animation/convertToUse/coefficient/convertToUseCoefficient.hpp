#pragma once

#include "../iConvertToUse.hpp"

namespace ui {
	template<typename T>
	class ConvertToUseCoefficient : public IConvertToUse<T>{
	protected:
		float coefficient;

		T convert(float value) override;

	public:
		explicit ConvertToUseCoefficient(float coefficient = 1);
	};

	template<typename T>
	bool convertPointer(const YAML::Node &node, ConvertToUseCoefficient<T>*& convertToUseCoefficient);
}

#include "convertToUseCoefficient.inl"