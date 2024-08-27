//included into Indexed.hpp

namespace ie {
	template<typename T_>
	Indexed<T_>::Indexed(T_&& object, size_t id) : id_(id), object_(std::make_unique<T_>(std::move(object))) {
	}
	
	template<typename T_>
	auto Indexed<T_>::make(absl::flat_hash_set<Indexed<T_> >& set) -> T_ const& {
		return (*set.insert(std::move(*(new Indexed<T_>{std::move(*this)}))).first->object_);
	}
	
	template<typename T_>
	auto Indexed<T_>::operator==(Indexed<T_> const& indexed) const -> bool {
		return (indexed.id_ == id_ && id_ != 0) || this == &indexed;
	}
	
	template<typename T_>
	auto Indexed<T_>::get_id() const -> size_t {
		return id_;
	}
}

template<typename T_>
auto std::hash<ie::Indexed<T_> >::operator()(ie::Indexed<T_> const& indexed) -> size_t{
	return indexed.get_id();
}

template<typename T_>
auto tnl::TypeName<ie::Indexed<T_> >::type_name() -> StringView {
	return tnl::type_name<T_>();
}

template<typename T>
auto ieml::Decode<char, ie::Indexed<T> >::decode(ieml::Node const& node) -> orl::Option<ie::Indexed<T> >{
	auto& tag_node{node.get_clear_data<ieml::NodeType::GetAnchor, ieml::NodeType::TakeAnchor>()};
	return ieml::Decode<char, T>::decode(tag_node).map([&](auto&& value) -> ie::Indexed<T> {
		if(&tag_node != &node) {
			size_t id{reinterpret_cast<size_t>(&tag_node)};
			return {std::move(value), id};
		}
		return {std::move(value)};
	});
}