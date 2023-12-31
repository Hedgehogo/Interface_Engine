#pragma once

#include <IEML/node.hpp>
#include <RTTB/Builder/Builder.hpp>

namespace rttb {
	template<>
	struct DecodePtr<ieml::Node const&> {
		template<typename Type_>
		static DecodePtrReturn<ieml::Decode<char, Type_>, ieml::Node const&, Type_*>
		decode(ieml::Node const& node) {
			auto result{ieml::Decode<char, Type_>::decode(node)};
			if(result.is_some()) {
				return new Type_{std::move(result.some())};
			}
			return {};
		}
	};
}

namespace ieml {
	template<typename Type_>
	struct Decode<char, Type_*> {
		using Return = std::enable_if_t<rttb::detail::has_decode_ptr_v<ieml::Node const&, Type_*>, orl::Option<Type_*> >;
		
		static Return decode(ieml::Node const& node) {
			auto const& clear_node{node.get_clear<NodeType::File, NodeType::TakeAnchor, NodeType::GetAnchor>()};
			if(auto type_name{clear_node.get_tag()}) {
				return rttb::Builder<ieml::Node const&, Type_>::builder().build(type_name.some(), node);
			} else {
				return rttb::Builder<ieml::Node const&, Type_>::builder().implicit_build(node);
			}
		}
	};
}
