#pragma once

#include <type_traits>

namespace ie::meta {
	template<template<typename> typename MetaFn_, typename... Types_>
	struct All : std::integral_constant<bool, true> {
	};
	
	template<template<typename> typename MetaFn_, typename First_, typename... Types_>
	struct All<MetaFn_, First_, Types_...> :
		std::integral_constant<bool, MetaFn_<First_>::value && All<MetaFn_, Types_...>::value> {
	};
	
	template<template<typename> typename MetaFn_, typename... Types_>
	constexpr auto all_v = All<MetaFn_, Types_...>::value;
}
