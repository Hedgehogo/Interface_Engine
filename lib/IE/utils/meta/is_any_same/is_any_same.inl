//included into is_any_same.hpp

namespace ie::meta {
	template<typename T>
	auto is_any_same(T const&) -> bool {
		return false;
	}
	
	template<typename T, typename F>
	auto is_any_same(T const& comp, F const& first) -> bool {
		return comp == first;
	}
	
	template<typename T, typename F, typename S, typename... V>
	auto is_any_same(T const& comp, F const& first, S const& second, V const&... values) -> bool {
		return comp == first || is_any_same<T>(comp, second, values...);
	}
}
