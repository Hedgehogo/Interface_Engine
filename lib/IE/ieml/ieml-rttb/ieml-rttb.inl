//included into ieml-rttb.hpp

namespace rttb {
	template<typename Type_>
	auto DecodePtr<const ieml::Node&>::decode(const ieml::Node& node) -> Return<Type_> {
		auto result{ieml::Decode<char, Type_>::decode(node)};
		if(result.is_some()) {
			return new Type_{std::move(result.some())};
		}
		return {};
	}
}

namespace ieml {
	template<typename Type_>
	auto Decode<char, Type_*>::decode(const Node& node) -> Return {
		auto& clear_node{node.get_clear_data<NodeType::Tag>()};
		if(&clear_node != &node) {
			auto type_name{node.get_tag()};
			return rttb::Builder<ieml::Node const&, Type_>::builder().build(type_name.some(), clear_node);
		}
		return rttb::Builder<ieml::Node const&, Type_>::builder().implicit_build(node);
	}
}

namespace ie {
	template<typename Type_>
	MakeDyn<Type_>::MakeDyn(size_t id, rttb::Dyn object) : id_(id), object_(std::move(object)) {
	}
	
	template<typename Type_>
	orl::Option<MakeDyn<Type_> > MakeDyn<Type_>::decode(const ieml::Node& node) {
		auto& tag_node{node.get_clear_data<ieml::NodeType::GetAnchor, ieml::NodeType::TakeAnchor>()};
		if(&tag_node != &node) {
			size_t id{reinterpret_cast<size_t>(&tag_node)};
			auto& clear_node{node.get_clear_data<ieml::NodeType::Tag>()};
			if(&clear_node != &node) {
				auto type_name{node.get_tag()};
				auto object{rttb::Builder<ieml::Node const&, Type_>::builder().build_dyn(type_name.some(), clear_node)};
				return {{id, std::move(object)}};
			}
			auto object{rttb::Builder<ieml::Node const&, Type_>::builder().implicit_build_dyn(node)};
			return {{id, std::move(object)}};
		}
		return {};
	}
	
	template<typename Type_>
	size_t MakeDyn<Type_>::get_id() const {
		return id_;
	}
	
	template<typename Type_>
	rttb::Dyn& MakeDyn<Type_>::get_object() {
		return object_;
	}
	
	template<typename Type_>
	rttb::Dyn const& MakeDyn<Type_>::get_object() const {
		return object_;
	}
}

template<typename Type_>
orl::Option<ie::MakeDyn<Type_> > ieml::Decode<char, ie::MakeDyn<Type_> >::decode(const ieml::Node& node) {
	return ie::MakeDyn<Type_>::decode(node);
}
