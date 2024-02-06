#pragma once

#include <type_traits>

namespace ie::meta {
	template<typename T_, typename... Ts_>
	struct IsContains : std::false_type {
	};
	
	template<typename T_, typename First_, typename... Ts_>
	struct IsContains<T_, First_, Ts_...> :
		std::integral_constant<bool, std::is_same_v<T_, First_> || IsContains<T_, Ts_...>::value> {
	};
	
	template<typename T_, typename... Ts_>
	constexpr auto is_contains_v = IsContains<T_, Ts_...>::value;
}
