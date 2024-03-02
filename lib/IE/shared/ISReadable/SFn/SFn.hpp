#pragma once

#include "../ISReadable.hpp"
#include "../../SReader/SReader.hpp"

namespace ie {
	namespace detail {
		template<typename T>
		using SFnMakeWrap = MakeDyn<std::remove_reference_t<T> >;
		
		template<typename T>
		using SFnWrap = SReader<std::remove_reference_t<T> >;
	}
	
	namespace make_system {
		template<auto Fn_>
		class SFn;
		
		template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
		class SFn<Fn_> : public ie::ToMutable<Value_>::Make {
		public:
			std::tuple<detail::SFnMakeWrap<Args_>...> args;
			
			SFn(typename ie::ToMutable<Value_>::Make make, detail::SFnMakeWrap<Args_>... args);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
	}
	
	template<auto Fn_>
	class SFn;
	
	template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
	class SFn<Fn_> : public ToMutable<Value_> {
	public:
		using T = typename ToMutable<Value_>::T;
		using ReadFn = typename ToMutable<Value_>::ReadFn;
		using Make = make_system::SFn<Fn_>;
		
		SFn(Make&& make, SInitInfo init_info);
		
	private:
		auto reset() -> void;
		
		std::tuple<detail::SFnWrap<Args_>...> args_;
	};
	
	namespace detail {
		template<typename SFn_, auto Fn_>
		struct ToSFn;
		
		template<typename Value_, typename... SArgs_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		struct ToSFn<Value_(SArgs_...), Fn_> {
			static auto fn(Value_ const&, SArgs_&... args) -> Return_;
			
			using type = SFn<fn>;
		};
	}
	
	template<typename SFn_, auto Fn_>
	using ToSFn = typename detail::ToSFn<SFn_, Fn_>::type;
}

template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
struct ieml::Decode<char, ie::make_system::SFn<Fn_> > {
	template<size_t... Index>
	static auto decode_args(ieml::ListView const& list, std::index_sequence<Index...>) -> std::tuple<ie::detail::SFnMakeWrap<Args_>...>;
	
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::SFn<Fn_> >;
};

#include "SFn.inl"
