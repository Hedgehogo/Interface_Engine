#pragma once

#include <vector>

namespace ie {
	std::vector<float>& addBounds(std::vector<float>& vector);
	
	std::vector<float> genBounds(std::size_t size);
	
	template<typename T>
	std::size_t y_size(std::vector<std::vector<T> >& vector) {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	namespace detail {
		template<typename T>
		void addItems(std::vector<T>&) {
		}
		
		template<typename T, typename A, typename... As>
		void addItems(std::vector<T>& vector, A&& arg, As&&... args) {
			vector.emplace_back(std::move(arg));
			addItems<T, As...>(vector, std::move(args)...);
		}
	}
	
	template<typename T, typename... As>
	std::vector<T> makeVector(T&& arg, As&&... args) {
		std::vector<T> result;
		result.reserve(sizeof...(As) + 1);
		detail::addItems<T, As...>(result, std::move(arg), std::move(args)...);
		return result;
	}
}