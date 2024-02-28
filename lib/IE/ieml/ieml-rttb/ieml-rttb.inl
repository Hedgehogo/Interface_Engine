//included into ieml-rttb.hpp

namespace rttb {
	template<typename Type_>
	auto DecodePtr<const ieml::Node&>::decode(const ieml::Node& node) -> Return<Type_> {
		return {new Type_{node.as<Type_>().except()}};
	}
}

namespace tnl {
	template<typename Type_>
	auto TypeName<Type_*>::type_name() -> StringView {
		static auto name{[] {
			auto name{tnl::type_name<Type_>()};
			return String{"dyn "} + String{name.begin(), name.end()};
		}()};
		return {name};
	}
}

namespace ieml {
	template<typename Type_>
	auto Decode<char, Type_*>::decode(const Node& node) -> orl::Option<Type_*> {
		auto& clear_node{node.get_clear_data<NodeType::Tag>()};
		auto& builder{rttb::Builder<ieml::Node const&, Type_>::builder()};
		if(&clear_node != &node) {
			auto& type_name{node.get_tag().some()};
			if(type_name == "_") {
				return builder.implicit_build(clear_node);
			}
			return builder.build(type_name, clear_node);
		}
		return builder.implicit_build(node);
	}
}
