#pragma once

#include "../SFn.hpp"
#include "../../ISRanged/SRanged/SRanged.hpp"

namespace ie {
	namespace detail {
		template<typename T_>
		struct SLerp {
			static T_ lerp(SRanged<T_> const& to, ISRanged<T_>& from);
		};
	}
	
	template<typename T_>
	using SLerp = SFn<detail::SLerp<T_>::lerp>;
	
	using SLerpF = SLerp<float>;
	using SLerpI = SLerp<int>;
	using SLerpS = SLerp<size_t>;
}

#include "SLerp.inl"
