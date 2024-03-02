#pragma once

#include "../SFn.hpp"
#include "../../SReadable/SReadable.hpp"

namespace ie {
	namespace detail {
		template<typename T_>
		struct SCompOp {
			static auto equal(T_ first, T_ second) -> bool;
			
			static auto not_equal(T_ first, T_ second) -> bool;
			
			static auto less(T_ first, T_ second) -> bool;
			
			static auto greater(T_ first, T_ second) -> bool;
			
			static auto less_or_equal(T_ first, T_ second) -> bool;
			
			static auto greater_or_equal(T_ first, T_ second) -> bool;
		};
	}
	
	template<typename T>
	using SEqual = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::equal>;
	
	template<typename T>
	using SNotEqual = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::not_equal>;
	
	template<typename T>
	using SLess = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::less>;
	
	template<typename T>
	using SGreater = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::greater>;
	
	template<typename T>
	using SLessOrEqual = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::less_or_equal>;
	
	template<typename T>
	using SGreaterOrEqual = ToSFn<SBool(ISReadable<T>&, ISReadable<T>&), detail::SCompOp<T>::greater_or_equal>;
}

#include "SCompOp.inl"
