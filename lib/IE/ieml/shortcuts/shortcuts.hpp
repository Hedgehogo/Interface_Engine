#pragma once

#include "IE/utils/meta/all_v/all_v.hpp"
#include "IE/utils/meta/is_string_v/is_string_v.hpp"
#include "../ieml-rttb/ieml-rttb.hpp"

namespace ie {
	namespace meta {
		template<typename... Types>
		constexpr auto is_names = meta::all_v<meta::IsString, std::decay_t<Types>...>;
	}
	
	template<typename Resource_, typename Type_>
	using NamedBuildFn = std::function<orl::Option<Type_*>(Resource_ resource)>;
	
	template<typename Type>
	auto add_names() -> void;
	
	template<typename Type, typename Name, typename... Names>
	auto add_names(Name name, Names... names) -> std::enable_if_t<meta::is_names<Name, Names...> >;
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type(Names... names) -> std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >;
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_named(Names... names) -> std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >;
	
	template<typename Type>
	auto add_fn(rttb::BuildFn<ieml::Node const&, Type> build_fn) -> void;
	
	template<typename Type, typename FirstName, typename... Names>
	auto add_fn(
		NamedBuildFn<ieml::Node const&, Type> build_fn, FirstName first_name, Names... names
	) -> std::enable_if_t<meta::is_names<FirstName, Names...> >;
	
	template<typename Type_>
	struct Determine {
	};
	
	namespace detail {
		template<typename Type_, typename = void>
		struct HasDetermine : std::false_type {
		};
		
		template<typename Type_>
		struct HasDetermine<Type_, std::void_t<decltype(Determine<Type_>::determine(std::declval<ieml::Node const&>()))> > : std::true_type {
		};
		
		template<typename Type_>
		constexpr auto has_determine_v = HasDetermine<Type_>::value;
	}
	
	template<typename Type>
	auto add_determine(rttb::DetermineFn<ieml::Node const&> determine_fn) -> void;
	
	template<typename Type>
	auto add_bool_determine(std::function<bool(ieml::Node const&)> determine_fn) -> void;
	
	template<typename Type>
	auto add_bool_determine() -> std::enable_if_t<detail::has_determine_v<Type> >;
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_make(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		meta::is_names<Names...>
	>;
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_with_make(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		std::is_base_of_v<Base, Derived> && meta::is_names<Names...>
	>;
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_make_named(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		meta::is_names<Names...>
	>;
	
	template<typename Type, typename FirstName, typename... Names>
	auto add_fn_make(
		NamedBuildFn<ieml::Node const&, typename Type::Make> build_fn,
		FirstName first_name,
		Names... names
	) -> std::enable_if_t<meta::is_names<FirstName, Names...> >;
	
	template<typename Type>
	auto add_determine_make(rttb::DetermineFn<ieml::Node const&> determine_fn) -> void;
	
	template<typename Type>
	auto add_bool_determine_make(std::function<bool(ieml::Node const&)> determine_fn) -> void;
	
	template<typename Type>
	auto add_bool_determine_make() -> std::enable_if_t<detail::has_determine_v<typename Type::Make> >;
}

#include "shortcuts.inl"
