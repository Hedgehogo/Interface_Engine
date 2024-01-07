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
		using Return = std::enable_if_t<rttb::detail::has_decode_ptr_v<ieml::Node const&, Type_*>, orl::Option<Type_*> >;
		
		static Return decode(ieml::Node const& node);
	};
}

namespace ie {
	template<typename Type_>
	class MakeDyn {
	public:
		using Data = std::variant<std::pair<size_t, rttb::Dyn>, std::string>;
		
		orl::Option<MakeDyn<Type_> > decode(ieml::Node const& node);
		
		size_t get_id() const;
		
		rttb::Dyn& get_object();
		
		rttb::Dyn const& get_object() const;
	
	private:
		MakeDyn(size_t id, rttb::Dyn object_);
		
		size_t id_;
		rttb::Dyn object_;
	};
}

template<typename Type_>
struct ieml::Decode<char, ie::MakeDyn<Type_> > {
	static orl::Option<ie::MakeDyn<Type_> > decode(ieml::Node const& node);
};

#include "ieml-rttb.inl"
