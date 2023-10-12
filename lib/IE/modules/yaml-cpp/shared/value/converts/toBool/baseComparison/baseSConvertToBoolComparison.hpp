#pragma once

#include "../../general/sConvertValue.hpp"

namespace ie {
	template<typename T>
	class BaseSConvertToBoolComparison : public SConvertToBool<T> {
	protected:
		virtual bool convert(T fromValue, T compared) = 0;
		
		bool convert(T fromValue) override;
		
	public:
		BaseSConvertToBoolComparison(PISValue<T> fromValue, bool defaultValue, T compared);
	
	protected:
		T compared;
	};
}

#include "baseSConvertToBoolComparison.inl"