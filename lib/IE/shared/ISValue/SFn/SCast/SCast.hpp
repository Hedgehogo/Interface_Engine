#pragma once
#include "../SFn.hpp"

namespace ie {
	namespace detail {
		template<typename From, typename To>
		struct SCast {
			static typename To::T fn(From& value);
		};
	}
	
	template<typename From, typename To>
	using BasicSCast = SFn<To, detail::SCast<From, To>::fn>;
	
	template<typename From, typename To>
	using SCast = BasicSCast<ISValue<From>, ISValue<To> >;
	
	using SCastF2I = SCast<float, int>;
	using SCastF2S = SCast<float, size_t>;
	using SCastI2F = SCast<int, float>;
	using SCastI2S = SCast<int, size_t>;;
	using SCastS2F = SCast<size_t, float>;
	using SCastS2I = SCast<size_t, int>;
}

#include "SCast.inl"
