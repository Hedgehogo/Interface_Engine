#pragma once

#include <IEML/node.hpp>
#include <RTTB/Builder/Builder.hpp>

namespace rttb {
	template<>
	struct DecodePtr<ieml::Node const&> {
		template<typename Type_>
		using Return = DecodePtrReturn<ieml::Decode<char, Type_>, ieml::Node const&, Type_*>;
		
		template<typename Type_>
		static auto decode(ieml::Node const& node) -> Return<Type_>;
	};
}

namespace tnl {
	template<typename Type_>
	struct TypeName<Type_*> {
		static auto type_name() -> StringView;
	};
}

namespace ieml {
	template<typename Type_>
	struct Decode<char, Type_*> {
		static auto decode(ieml::Node const& node) -> orl::Option<Type_*>;
	};
}

#include "ieml-rttb.inl"
