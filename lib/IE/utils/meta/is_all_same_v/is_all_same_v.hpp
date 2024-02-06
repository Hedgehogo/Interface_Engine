#pragma once

#include <type_traits>

namespace ie::meta {
	template<typename... Types>
	struct IsAllSame : std::integral_constant<bool, true> {
	};
	
	template<typename First_, typename Second_, typename... Types_>
	struct IsAllSame<First_, Second_, Types_...> :
		std::integral_constant<bool, std::is_same_v<First_, Second_> && IsAllSame<Second_, Types_...>::value> {
	};

	template<typename Type, typename... Types>
	constexpr auto is_all_same_v = IsAllSame<Type, Types...>::value;
}
