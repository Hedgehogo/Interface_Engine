#pragma once

#include "../ISReadable.hpp"

namespace ie {
	namespace make_system {
		template<typename T_>
		struct ISRanged : public virtual ISReadable<T_> {
		};
		
		template<typename T_>
		struct ToMutable<ISRanged<T_> > : public virtual ISRanged<T_>, public virtual ISMutable<T_> {
		};
		
		template<typename T_>
		using ISMRanged = ToMutable<ISRanged<T_> >;
	}
	
	template<typename T_>
	class ISRanged : public virtual ISReadable<T_> {
	public:
		using T = T_;
		using ReadFn = typename ISReadable<T_>::ReadFn;
		using Make = make_system::ISRanged<T_>;
		
		virtual T_ get_upper_bound() const = 0;
		
		virtual T_ get_lower_bound() const = 0;
		
		virtual void set_upper_bound(T_ upper_bound) = 0;
		
		virtual void set_lower_bound(T_ lower_bound) = 0;
		
		virtual void set_bounds(T_ lower_bound, T_ upper_bound);
	};
	
	using ISRFloat = ISRanged<float>;
	using ISRInt = ISRanged<int>;
	using ISRSize = ISRanged<size_t>;
	
	template<typename T_>
	class ToMutable<ISRanged<T_> > : public virtual ISRanged<T_>, public virtual ISMutable<T_> {
	public:
		using T = typename ISRanged<T_>::T;
		using ReadFn = typename ISRanged<T_>::ReadFn;
		using Make = make_system::ISMRanged<T_>;
	};
	
	template<typename T_>
	using ISMRanged = ToMutable<ISRanged<T_> >;
	
	using ISMRFloat = ISMRanged<float>;
	using ISMRInt = ISMRanged<int>;
	using ISMRSize = ISMRanged<size_t>;
}

#include "ISRanged.inl"