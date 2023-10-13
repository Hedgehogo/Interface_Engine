#include "Vector.hpp"
#include <algorithm>

namespace ie {
	std::vector<float>& addBounds(std::vector<float>& vector) {
		vector.reserve(vector.size() + 2);
		vector.push_back(0.f);
		std::rotate(vector.rbegin(), vector.rbegin() + 1, vector.rend());
		vector.push_back(1.f);
		return vector;
	}
	
	std::vector<float> genBounds(std::size_t size) {
		std::vector<float> vector;
		vector.reserve(size + 1);
		for(std::size_t i = 0; i < size; ++i) {
			vector.push_back(static_cast<float>(i) / static_cast<float>(size));
		}
		vector.push_back(1.f);
		return vector;
	}
}