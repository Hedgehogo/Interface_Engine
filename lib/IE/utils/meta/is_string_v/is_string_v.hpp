#pragma once

#include <type_traits>
#include <string>

namespace ie::meta {
	template<typename Type_>
	struct IsString : std::integral_constant<bool, false> {
	};
	
	template<>
	struct IsString<const char*> : std::integral_constant<bool, true> {
	};
	
	template<>
	struct IsString<std::string> : std::integral_constant<bool, true> {
	};
	
	template<typename Type>
	constexpr auto is_string_v = IsString<Type>::value;
}
