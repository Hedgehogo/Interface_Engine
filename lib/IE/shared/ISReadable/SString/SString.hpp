#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../ISReadable.hpp"

namespace ie {
	namespace make_system {
		struct SString : public virtual ISReadable<std::u32string_view> {
		public:
			std::u32string data;
			
			SString(std::u32string data = {});
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		template<>
		struct ToMutable<SString> : public SString, public virtual ISMutable<std::u32string_view> {
		public:
			ToMutable(std::u32string data = {});
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
		
		using SMString = ToMutable<SString>;
	}
}

template<>
struct ieml::Decode<char, ie::make_system::SString> {
	static orl::Option<ie::make_system::SString> decode(ieml::Node const& node);
};

template<>
struct ieml::Decode<char, ie::make_system::SMString> {
	static orl::Option<ie::make_system::SMString> decode(ieml::Node const& node);
};

namespace ie {
	class SString : public virtual ISReadable<std::u32string_view> {
	public:
		using T = ISReadable<std::u32string_view>::T;
		using ReadFn = ISReadable<std::u32string_view>::ReadFn;
		using Make = make_system::SString;
		
		SString(Make&& make, DynBuffer&);
		
		SString(std::u32string data);
		
		std::u32string_view get() const override;
	
	protected:
		ReadFn& add_read_fn(ReadFn&& read_fn) override;
		
		bool delete_read_fn(ReadFn& read_fn) override;
		
		std::u32string data_;
		std::vector<ReadFn> read_fns_;
	};
	
	template<>
	class ToMutable<SString> : public SString, public virtual ISMutable<std::u32string_view> {
	public:
		using T = SString::T;
		using ReadFn = ISMutable<std::u32string_view>::ReadFn;
		using Make = make_system::SMString;
		
		ToMutable(Make&& make, DynBuffer&);
		
		ToMutable(std::u32string data);
		
		void set(std::u32string_view value) override;
	};
	
	using SMString = ToMutable<SString>;
	
	template<>
	struct Determine<SMString::Make> {
		static bool determine(ieml::Node const& node);
	};
}
