#pragma once

#include "../../general/sConvertValue.hpp"

namespace ui {
	template<typename T>
	class BaseSConvertToBoolComparison : public SConvertToBool<T> {
	protected:
		virtual bool convert(T fromValue, T compared) = 0;
		
		bool convert(T fromValue) override;
		
		T compared;
	public:
		BaseSConvertToBoolComparison(PISValue<T> fromValue, bool defaultValue, T compared);
		
	};
}

#include "baseSConvertToBoolComparison.inl"