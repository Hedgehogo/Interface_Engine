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
	void add_names();
	
	template<typename Type, typename Name, typename... Names>
	std::enable_if_t<meta::is_names<Name, Names...> >
	add_names(Name name, Names... names);
	
	template<typename Base, typename Derived, typename... Names>
	std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >
	add_type(Names... names);
	
	template<typename Base, typename Derived, typename... Names>
	std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >
	add_type_named(Names... names);
	
	template<typename Type>
	void add_fn(rttb::BuildFn<ieml::Node const&, Type> build_fn);
	
	template<typename Type, typename FirstName, typename... Names>
	std::enable_if_t<meta::is_names<FirstName, Names...> >
	add_fn(NamedBuildFn<ieml::Node const&, Type> build_fn, FirstName first_name, Names... names);
	
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
	void add_determine(rttb::DetermineFn<ieml::Node const&> determine_fn);
	
	template<typename Type>
	std::enable_if_t<detail::has_determine_v<Type> > add_determine();
}

#include "shortcuts.inl"
