#pragma once
#include <array>

namespace ie{
	template<size_t S, typename F>
	auto array_from_fn(F fn) -> std::array<std::invoke_result_t<F>, S>;
	
	template<size_t S, size_t I = 0, typename F, typename... As>
	auto array_try_from_fn(F fn, As&&... args) -> orl::Result<
		std::array<typename std::invoke_result_t<F, size_t>::OkType, S>,
		typename std::invoke_result_t<F, size_t>::ErrorType
	>;
}

#include "array.inl"