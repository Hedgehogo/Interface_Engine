#pragma once

#include "../ISValue.hpp"

namespace ie {
	template<typename FromType, typename ToType>
	class ISConvertValue : public virtual ISValue<ToType> {
	public:
		using PFromType = PISValue<FromType>;
	};
}