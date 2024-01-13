#pragma once

#include "../ISValue/ISValue.hpp"

namespace ie {
	template<typename T_>
	class ISRanged;
	
	namespace make_system {
		template<typename T_>
		struct ISRanged : public virtual ISValue<T_> {
		};
	}
	
	template<typename T_>
	class ISRanged : public virtual ISValue<T_> {
	public:
		using ReadFn = typename ISValue<T_>::ReadFn;
		using Make = make_system::ISRanged<T_>;
		
		virtual T_ get_upper_bound() = 0;
		
		virtual T_ get_lower_bound() = 0;
		
		virtual void set_upper_bound(T_ upper_bound) = 0;
		
		virtual void set_lower_bound(T_ lower_bound) = 0;
		
		virtual void set_bounds(T_ lower_bound, T_ upper_bound);
	};
	
	using ISRFloat = ISRanged<float>;
	using ISRInt = ISRanged<int>;
	using ISRSize = ISRanged<size_t>;
}

#include "ISRanged.inl"