#pragma once

#include <absl/container/flat_hash_set.h>
#include <box-ptr/BoxPtr.hpp>
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	template<typename T_>
	class Indexed {
	public:
		Indexed(T_&& object, size_t id = 0);
		
		auto make(absl::flat_hash_set<bp::BoxPtr<Indexed<T_>, true> >& set) -> T_ const&;
		
		auto get_id() const -> size_t;
		
		auto operator==(Indexed<T_> const& indexed) const -> bool;
	
	protected:
		size_t id_;
		T_ object_;
	};
}

template<typename T_>
struct std::hash<ie::Indexed<T_> >{
	auto operator()(ie::Indexed<T_> const& indexed) -> size_t;
};

template<typename T_>
struct tnl::TypeName<ie::Indexed<T_> > {
	static auto type_name() -> StringView;
};

template<typename T>
struct ieml::Decode<char, ie::Indexed<T> > {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Indexed<T> >;
};

#include "Indexed.inl"