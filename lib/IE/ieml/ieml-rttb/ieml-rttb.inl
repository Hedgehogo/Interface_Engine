//included into ieml-rttb.hpp

namespace rttb {
	template<typename Type_>
	auto DecodePtr<const ieml::Node&>::decode(const ieml::Node& node) -> Return<Type_> {
		auto result{ieml::Decode<char, Type_>::decode(node)};
		if(result.is_some()) {
			return new Type_{result.move_some()};
		}
		return {};
	}
}

namespace ieml {
	template<typename Type_>
	auto Decode<char, Type_*>::decode(const Node& node) -> orl::Option<Type_*> {
		auto& clear_node{node.get_clear_data<NodeType::Tag>()};
		if(&clear_node != &node) {
			auto type_name{node.get_tag()};
			return rttb::Builder<ieml::Node const&, Type_>::builder().build(type_name.some(), clear_node);
		}
		return rttb::Builder<ieml::Node const&, Type_>::builder().implicit_build(node);
	}
}
