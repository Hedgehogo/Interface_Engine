#pragma once

#include "../ISReadable.hpp"
#include "../../SReader/SReader.hpp"

namespace ie {
	namespace detail {
		template<typename T>
		using SFnMakeWrap = MakeDyn<std::remove_reference_t<T> >;
		
		template<typename T>
		using SFnWrap = SReader<std::remove_reference_t<T> >;
		
		template<typename FnType_>
		struct SFnImpl;
		
		namespace make_system {
			template<typename FnType_>
			struct SFnImpl;
			
			template<typename Return_, typename... Args_>
			struct SFnImpl<Return_(*)(Args_...)> {
				template<typename Result_, Return_(* Fn_)(Args_...)>
				struct Type : public Result_::Make {
					std::tuple<SFnMakeWrap<Args_>...> args;
					
					using Return = typename ie::detail::SFnImpl<Return_(*)(Args_...)>::template Type<Result_, Fn_>;
					
					Type(SFnMakeWrap<Args_>... args);
					
					rttb::Dyn make(DynBuffer& dyn_buffer) override;
				};
			};
		}
		
		template<typename Return_, typename... Args_>
		struct SFnImpl<Return_(*)(Args_...)> {
			template<typename Result_, Return_(* Fn_)(Args_...)>
			class Type : public Result_ {
			public:
				using T = typename Result_::T;
				using ReadFn = typename Result_::ReadFn;
				using Make = typename make_system::SFnImpl<Return_(*)(Args_...)>::template Type<Result_, Fn_>;
				
				Type(Make&& make, DynBuffer& dyn_buffer);
				
				T get() const override;
				
			protected:
				ReadFn& add_read_fn(ReadFn&& read_fn) override;
				
				bool delete_read_fn(ReadFn& read_fn) override;
			
			private:
				void reset();
				
				std::tuple<SFnWrap<Args_>...> args_;
				std::vector<ReadFn> read_fns_;
			};
		};
	}
	
	namespace make_system {
		template<typename Result_, auto Fn_>
		class SFn : public detail::make_system::SFnImpl<decltype(Fn_)>::template Type<Result_, Fn_> {
		public:
			template<typename... Ts>
			SFn(Ts... args);
		};
	}
	
	template<typename Result_, auto Fn_>
	class SFn : public detail::SFnImpl<decltype(Fn_)>::template Type<Result_, Fn_> {
	public:
		using Make = make_system::SFn<Result_, Fn_>;
		
		template<typename... Ts>
		SFn(Ts... args);
	};
}

template<typename Result_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
struct ieml::Decode<char, ie::make_system::SFn<Result_, Fn_> > {
	template<size_t... Index>
	static std::tuple<ie::detail::SFnMakeWrap<Args_>...> decode_args(ieml::ListView const& list, std::index_sequence<Index...>);
	
	static orl::Option<ie::make_system::SFn<Result_, Fn_> > decode(ieml::Node const& node);
};

#include "SFn.inl"
