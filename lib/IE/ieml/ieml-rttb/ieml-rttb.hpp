#pragma once

#include <IEML/node.hpp>
#include <RTTB/Builder/Builder.hpp>

namespace rttb {
	template<>
	struct DecodePtr<ieml::Node const&> {
		template<typename Type_>
		using Return = DecodePtrReturn<ieml::Decode<char, Type_>, ieml::Node const&, Type_*>;
		
		template<typename Type_>
		static Return<Type_> decode(ieml::Node const& node);
	};
}

namespace ieml {
	template<typename Type_>
	struct Decode<char, Type_*> {
		static orl::Option<Type_*> decode(ieml::Node const& node);
	};
}

#include "ieml-rttb.inl"
