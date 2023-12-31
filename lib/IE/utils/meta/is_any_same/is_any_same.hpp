#pragma once
#include <utility>

namespace ie::meta {
	template<typename T>
	bool is_any_same(T const& comp);
	
	template<typename T, typename F>
	bool is_any_same(T const& comp, F const& first);
	
	template<typename T, typename F, typename S, typename... V>
	bool is_any_same(T const& comp, F const& first, S const& second, V const&... values);
}

#include "is_any_same.inl"