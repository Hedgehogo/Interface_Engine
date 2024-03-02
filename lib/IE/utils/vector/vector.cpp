#include "vector.hpp"
#include <algorithm>

namespace ie {
	auto add_bounds(std::vector<float>& vector) -> std::vector<float>& {
		vector.reserve(vector.size() + 2);
		vector.push_back(0.f);
		std::rotate(vector.rbegin(), vector.rbegin() + 1, vector.rend());
		vector.push_back(1.f);
		return vector;
	}
	
	auto gen_bounds(size_t size) -> std::vector<float> {
		auto vector{std::vector<float>{}};
		vector.reserve(size + 1);
		for(size_t i = 0; i < size; ++i) {
			vector.push_back(static_cast<float>(i) / static_cast<float>(size));
		}
		vector.push_back(1.f);
		return vector;
	}
}