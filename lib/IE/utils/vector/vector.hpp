#pragma once

#include <vector>

namespace ie {
	std::vector<float>& add_bounds(std::vector<float>& vector);
	
	std::vector<float> gen_bounds(std::size_t size);
	
	template<typename T>
	std::size_t y_size(std::vector<std::vector<T> >& vector) {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	namespace detail {
		template<typename T>
		void add_items(std::vector<T>&) {
		}
		
		template<typename T, typename A, typename... As>
		void add_items(std::vector<T>& vector, A&& arg, As&&... args) {
			vector.emplace_back(std::move(arg));
			add_items<T, As...>(vector, std::move(args)...);
		}
	}
	
	template<typename T, typename... As>
	std::vector<T> make_vector(T&& arg, As&&... args) {
		std::vector<T> result;
		result.reserve(sizeof...(As) + 1);
		detail::add_items<T, As...>(result, std::move(arg), std::move(args)...);
		return result;
	}
}