//included into vector.hpp

namespace ie {
	template<typename T>
	auto y_size(std::vector<std::vector<T>>& vector) -> size_t {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	template<typename T, typename... As>
	auto make_vector(T&& first, As&& ... args) -> std::vector<T> {
		auto result{std::vector<T>{}};
		result.reserve(sizeof...(As) + 1);
		result.emplace_back(std::forward<T>(first));
		(static_cast<void>(result.emplace_back(std::forward<T>(args))), ...);
		return result;
	}
}
