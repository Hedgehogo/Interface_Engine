//included into shortcuts.hpp

#include "IE/utils/meta/is_any_same/is_any_same.hpp"
#include "IE/utils/meta/remove_namespace/remove_namespace.hpp"

namespace ie {
	template<typename Type>
	void add_names() {
	}
	
	template<typename Type, typename Name, typename... Names>
	std::enable_if_t<meta::is_names<Name, Names...> >
	add_names(Name name, Names... names) {
		rttb::Builder<ieml::Node const&, Type>::builder().add_name(std::forward<Name>(name));
		add_names<Type, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >
	add_type(Names... names) {
		rttb::Builder<ieml::Node const&, Base>::builder().template add_type<Derived>();
		add_names<Derived, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	std::enable_if_t<std::is_base_of_v<Base, Derived> && meta::is_names<Names...> >
	add_type_named(Names... names) {
		std::string type_name{ieml::get_type_name<Derived>()};
		add_names<Derived>(std::string{meta::remove_namespace(type_name)});
		add_type<Base, Derived, Names...>(names...);
	}
	
	template<typename Type>
	void add_fn(rttb::BuildFn<ieml::Node const&, Type> build_fn) {
		rttb::Builder<ieml::Node const&, Type>::builder().add_fn(std::move(build_fn));
	}
	
	template<typename Type, typename FirstName, typename... Names>
	std::enable_if_t<meta::is_names<FirstName, Names...> >
	add_fn(
		NamedBuildFn<ieml::Node const&, Type> build_fn,
		FirstName first_name,
		Names... names
	) {
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
	void add_determine(rttb::DetermineFn<ieml::Node const&> determine_fn) {
		rttb::Builder<ieml::Node const&, Type>::builder().add_determine(std::move(determine_fn));
	}
	
	template<typename Type>
	std::enable_if_t<detail::has_determine_v<Type> > add_determine() {
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
	std::enable_if_t<std::is_base_of_v<typename Base::Make, typename Derived::Make> && meta::is_names<Names...> >
	add_type_make(Names... names) {
		add_type<typename Base::Make, typename Derived::Make, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Base, typename Derived, typename... Names>
	std::enable_if_t<std::is_base_of_v<typename Base::Make, typename Derived::Make> && meta::is_names<Names...> >
	add_type_make_named(Names... names) {
		std::string type_name{ieml::get_type_name<Derived>()};
		add_names<typename Derived::Make>(std::string{meta::remove_namespace(type_name)});
		add_type_make<Base, Derived, Names...>(std::forward<Names>(names)...);
	}
	
	template<typename Type, typename FirstName, typename... Names>
	std::enable_if_t<meta::is_names<FirstName, Names...> >
	add_fn_make(
		NamedBuildFn<ieml::Node const&, typename Type::Make> build_fn,
		FirstName first_name,
		Names... names
	) {
		add_fn<typename Type::Make, FirstName, Names...>(std::move(build_fn), std::forward<FirstName>(first_name), std::forward<Names>(names)...);
	}
	
	template<typename Type>
	void add_determine_make(rttb::DetermineFn<ieml::Node const&> determine_fn) {
		add_determine<typename Type::Make>(std::move(determine_fn));
	}
	
	template<typename Type>
	std::enable_if_t<detail::has_determine_v<typename Type::Make> > add_determine_make() {
		add_determine<typename Type::Make>();
	}
}