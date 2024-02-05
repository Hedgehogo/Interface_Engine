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
		template<typename Result_, auto Fn_>
		class SFn;
		
		template<typename Result_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		struct SFn<Result_, Fn_> : public Result_::Make {
			std::tuple<detail::SFnMakeWrap<Args_>...> args;
			
			SFn(detail::SFnMakeWrap<Args_>... args);
			
			rttb::Dyn make(DynBuffer& dyn_buffer) override;
		};
	}
	
	template<typename Result_, auto Fn_>
	class SFn;
	
	template<typename Result_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
	class SFn<Result_, Fn_> : public Result_ {
	public:
		using T = typename Result_::T;
		using ReadFn = typename Result_::ReadFn;
		using Make = make_system::SFn<Result_, Fn_>;
		
		SFn(Make&& make, DynBuffer& dyn_buffer);
		
		T get() const override;
	
	protected:
		ReadFn& add_read_fn(ReadFn&& read_fn) override;
		
		bool delete_read_fn(ReadFn& read_fn) override;
	
	private:
		void reset();
		
		std::tuple<detail::SFnWrap<Args_>...> args_;
		std::vector<ReadFn> read_fns_;
	};
}

template<typename Result_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
struct ieml::Decode<char, ie::make_system::SFn<Result_, Fn_> > {
	template<size_t... Index>
	static std::tuple<ie::detail::SFnMakeWrap<Args_>...> decode_args(ieml::ListView const& list, std::index_sequence<Index...>);
	
	static orl::Option<ie::make_system::SFn<Result_, Fn_> > decode(ieml::Node const& node);
};

#include "SFn.inl"
