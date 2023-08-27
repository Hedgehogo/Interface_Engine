#pragma once

#include "../iSValue.hpp"

namespace ie {
	template<typename FromType, typename ToType>
	class ISConvertValue : public virtual ISValue<ToType> {
	public:
		using PFromType = PISValue<FromType>;
	};
}