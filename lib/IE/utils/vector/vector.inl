//included into vector.hpp

namespace ie {
	template<typename T>
	auto y_size(std::vector<std::vector<T>>& vector) -> size_t {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	namespace detail {
		template<typename T>
		auto add_items(std::vector<T>&) -> void {
		}
		
		template<typename T, typename A, typename... As>
		auto add_items(std::vector<T>& vector, A&& arg, As&& ... args) -> void {
			vector.emplace_back(std::move(arg));
			add_items<T, As...>(vector, std::move(args)...);
		}
	}
	
	template<typename T, typename... As>
	auto make_vector(T&& arg, As&& ... args) -> std::vector<T> {
		auto result{std::vector<T>{}};
		result.reserve(sizeof...(As) + 1);
		detail::add_items<T, As...>(result, std::move(arg), std::move(args)...);
		return result;
	}
}
