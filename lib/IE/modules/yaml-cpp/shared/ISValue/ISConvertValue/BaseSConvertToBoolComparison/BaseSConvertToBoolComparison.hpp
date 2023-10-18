#pragma once

#include "../SConvertValue/SConvertValue.hpp"

namespace ie {
	template<typename T>
	class BaseSConvertToBoolComparison : public SConvertToBool<T> {
	protected:
		virtual bool convert(T from_value, T compared) = 0;
		
		bool convert(T from_value) override;
		
	public:
		BaseSConvertToBoolComparison(PISValue<T> from_value, bool default_value, T compared);
	
	protected:
		T compared;
	};
}

#include "BaseSConvertToBoolComparison.inl"