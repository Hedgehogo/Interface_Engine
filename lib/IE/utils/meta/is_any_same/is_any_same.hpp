#pragma once
#include <utility>

namespace ie::meta {
	template<typename T>
	auto is_any_same(T const& comp) -> bool;
	
	template<typename T, typename F>
	auto is_any_same(T const& comp, F const& first) -> bool;
	
	template<typename T, typename F, typename S, typename... V>
	auto is_any_same(T const& comp, F const& first, S const& second, V const&... values) -> bool;
}

#include "is_any_same.inl"