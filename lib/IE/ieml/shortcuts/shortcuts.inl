//included into shortcuts.hpp

#include <IEML/helpers/unstable_type_name/unstable_type_name.hpp>
#include "IE/utils/meta/is_any_same/is_any_same.hpp"
#include "IE/utils/meta/remove_namespace/remove_namespace.hpp"

namespace ie {
	template<typename Type>
	auto add_names() -> void {
	}
	
	template<typename Type, typename Name, typename... Names>
	auto add_names(Name name, Names... names) -> std::enable_if_t<meta::is_names<Name, Names...> > {
		rttb::Builder<ieml::Node const&, Type>::builder().add_name(std::forward<Name>(name));
		add_names<Type, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type(Names... names) -> std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> > {
		rttb::Builder<ieml::Node const&, Base>::builder().template add_type<Derived>();
		add_names<Derived, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_named(Names... names) -> std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> > {
		std::string type_name{ieml::unstable_type_name<Derived>()};
		add_names<Derived>(std::string{meta::remove_namespace(type_name)});
		add_type<Base, Derived, Names...>(names...);
	}
	
	template<typename Type>
	auto add_fn(rttb::BuildFn<ieml::Node const&, Type> build_fn) -> void {
		rttb::Builder<ieml::Node const&, Type>::builder().add_fn(std::move(build_fn));
	}
	
	template<typename Type, typename FirstName, typename... Names>
	auto add_fn(
		NamedBuildFn<ieml::Node const&, Type> build_fn,
		FirstName first_name,
		Names... names
	) -> std::enable_if_t<meta::is_names<FirstName, Names...> > {
		rttb::Builder<ieml::Node const&, Type>::builder().add_fn(
			[
				build_fn = std::move(build_fn),
				names_tuple = std::make_tuple(std::forward<FirstName>(first_name), std::forward<Names>(names)...)
			](std::string const& name, ieml::Node const& node) -> orl::Option<Type*> {
				return std::apply([&](auto const& ... names) -> orl::Option<Type*> {
					if(meta::is_any_same(name, names...)) {
						return build_fn(node);
					}
					return {};
				}, names_tuple);
			}
		);
	}
	
	template<typename Type>
	auto add_determine(rttb::DetermineFn<ieml::Node const&> determine_fn) -> void {
		rttb::Builder<ieml::Node const&, Type>::builder().add_determine(std::move(determine_fn));
	}
	
	template<typename Type>
	auto add_bool_determine(std::function<bool(ieml::Node const&)> determine_fn) -> void {
		rttb::Builder<ieml::Node const&, Type>::builder().add_determine(
			[determine_fn = std::move(determine_fn)]
				(ieml::Node const& node) -> orl::Option<std::string> {
				if(determine_fn(node)) {
					auto& names{rttb::Builder<ieml::Node const&, Type>::builder().get_names()};
					if(!names.empty()) {
						return *names.cbegin();
					}
				}
				return {};
			}
		);
	}
	
	template<typename Type>
	auto add_bool_determine() -> std::enable_if_t<detail::has_determine_v<Type> > {
		rttb::Builder<ieml::Node const&, Type>::builder().add_determine(
			[](ieml::Node const& node) -> orl::Option<std::string> {
				if(Determine<Type>::determine(node)) {
					auto& names{rttb::Builder<ieml::Node const&, Type>::builder().get_names()};
					if(!names.empty()) {
						return *names.cbegin();
					}
				}
				return {};
			}
		);
	}
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_make(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		meta::is_names<Names...>
	> {
		add_type<typename Base::Make, typename Derived::Make, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_make_named(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		meta::is_names<Names...>
	> {
		std::string type_name{ieml::unstable_type_name<Derived>()};
		add_names<typename Derived::Make>(std::string{meta::remove_namespace(type_name)});
		add_type_make<Base, Derived, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	auto add_type_with_make(Names... names) -> std::enable_if_t<
		std::is_base_of_v<typename Base::Make, typename Derived::Make> &&
		std::is_base_of_v<Base, Derived> && meta::is_names<Names...>
	> {
		add_type<Base, Derived>();
		add_type_make<Base, Derived>(std::forward<Names>(names)...);
	}
	
	template<typename Type, typename FirstName, typename... Names>
	auto add_fn_make(
		NamedBuildFn<ieml::Node const&, typename Type::Make> build_fn,
		FirstName first_name,
		Names... names
	) -> std::enable_if_t<meta::is_names<FirstName, Names...> > {
		add_fn<typename Type::Make, FirstName, Names...>(std::move(build_fn), std::forward<FirstName>(first_name), std::forward<Names>(names)...);
	}
	
	template<typename Type>
	auto add_determine_make(rttb::DetermineFn<ieml::Node const&> determine_fn) -> void {
		add_determine<typename Type::Make>(std::move(determine_fn));
	}
	
	template<typename Type>
	auto add_bool_determine_make(std::function<bool(ieml::Node const&)> determine_fn) -> void {
		add_bool_determine<typename Type::Make>(std::move(determine_fn));
	}
	
	template<typename Type>
	auto add_bool_determine_make() -> std::enable_if_t<detail::has_determine_v<typename Type::Make> > {
		add_bool_determine<typename Type::Make>();
	}
}