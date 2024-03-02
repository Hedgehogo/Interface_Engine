#pragma once

#include <vector>
#include <cstddef>

namespace ie {
	auto add_bounds(std::vector<float>& vector) -> std::vector<float>&;
	
	auto gen_bounds(size_t size) -> std::vector<float>;
	
	template<typename T>
	auto y_size(std::vector<std::vector<T> >& vector) -> size_t;
	
	template<typename T, typename... As>
	auto make_vector(T&& arg, As&&... args) -> std::vector<T>;
}

#include "vector.inl"
