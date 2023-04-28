#pragma once

#include "../iSValue.hpp"

namespace ui {
	template<typename FromType, typename ToType>
	class ISConvertValue : virtual public ISValue<ToType> {
	public:
		using PFromType = PISValue<FromType>;
	};
}