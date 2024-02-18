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
		template<typename Value_, auto Fn_>
		class SFn;
		
		template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		struct SFn<Value_, Fn_> : public ie::ToMutable<Value_>::Make {
			std::tuple<detail::SFnMakeWrap<Args_>...> args;
			
			SFn(typename ie::ToMutable<Value_>::Make make, detail::SFnMakeWrap<Args_>... args);
			
			rttb::Dyn make(SInitInfo init_info) override;
		};
	}
	
	template<typename Value_, auto Fn_>
	class SFn;
	
	template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
	class SFn<Value_, Fn_> : public ToMutable<Value_> {
	public:
		using T = typename ToMutable<Value_>::T;
		using ReadFn = typename ToMutable<Value_>::ReadFn;
		using Make = make_system::SFn<Value_, Fn_>;
		
		SFn(Make&& make, SInitInfo init_info);
		
	private:
		void reset();
		
		std::tuple<detail::SFnWrap<Args_>...> args_;
	};
}

template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
struct ieml::Decode<char, ie::make_system::SFn<Value_, Fn_> > {
	template<size_t... Index>
	static std::tuple<ie::detail::SFnMakeWrap<Args_>...> decode_args(ieml::ListView const& list, std::index_sequence<Index...>);
	
	static orl::Option<ie::make_system::SFn<Value_, Fn_> > decode(ieml::Node const& node);
};

#include "SFn.inl"
