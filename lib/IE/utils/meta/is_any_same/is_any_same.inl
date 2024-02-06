//included into is_any_same.hpp

namespace ie::meta {
	template<typename T>
	bool is_any_same(T const&) {
		return false;
	}
	
	template<typename T, typename F>
	bool is_any_same(T const& comp, F const& first) {
		return comp == first;
	}
	
	template<typename T, typename F, typename S, typename... V>
	bool is_any_same(T const& comp, F const& first, S const& second, V const&... values) {
		return comp == first || is_any_same<T>(comp, second, values...);
	}
}
