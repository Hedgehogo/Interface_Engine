#pragma once

#include <vector>
#include <cstddef>
#include <option_result/option_result.hpp>

namespace ie {
	auto add_bounds(std::vector<float>& vector) -> std::vector<float>&;
	
	auto gen_bounds(size_t size) -> std::vector<float>;
	
	template<typename T>
	auto y_size(std::vector<std::vector<T> >& vector) -> size_t;
	
	template<typename T, typename... As>
	auto make_vector(T&& first, As&&... args) -> std::vector<T>;
	
	template<typename F>
	auto vector_from_fn(size_t size, F fn) -> std::vector<std::invoke_result_t<F, size_t> >;
	
	template<typename F>
	auto vector_try_from_fn(size_t size, F fn) -> orl::Result<
		std::vector<typename std::invoke_result_t<F, size_t>::OkType>,
		typename std::invoke_result_t<F, size_t>::ErrorType
	>;
}

#include "vector.inl"
