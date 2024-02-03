//included into SFn.hpp

namespace ie {
	namespace detail {
		namespace make_system {
			template<typename Return_, typename... Args_>
			template<typename Result_, Return_ (* Fn_)(Args_...)>
			SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::Type(SFnMakeWrap<Args_>... args) :
				args(std::make_tuple(std::forward<SFnMakeWrap<Args_> >(args)...)) {
			}
			
			template<typename Return_, typename... Args_>
			template<typename Result_, Return_ (* Fn_)(Args_...)>
			rttb::Dyn SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::make(DynBuffer& dyn_buffer) {
				return rttb::Dyn{Return{std::move(*this), dyn_buffer}};
			}
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::Type(Make&& make, DynBuffer& dyn_buffer) :
			args_(std::apply([&dyn_buffer, this](SFnMakeWrap<Args_>&&... args) {
				return std::make_tuple(
					SFnWrap<Args_>{
						dyn_buffer.get(std::move(args)),
						[this](Return_ const&) {
							this->reset();
						}
					}...
				);
			}, std::move(make.args))) {
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		auto SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::get() const -> T {
			return std::apply([&](SFnWrap<Args_> const&... args) {
				return Fn_(args.get()...);
			}, args_);
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		void SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::set(T) {
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		auto SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::add_read_fn(ReadFn&& read_fn) -> ReadFn& {
			return read_fns_.emplace_back(std::move(read_fn));
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		bool SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::delete_read_fn(ReadFn& read_fn) {
			auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
				return &item == &read_fn;
			})};
			if(result != read_fns_.cend()) {
				read_fns_.erase(result);
				return true;
			}
			return false;
		}
		
		template<typename Return_, typename... Args_>
		template<typename Result_, Return_(* Fn_)(Args_...)>
		void SFnImpl<Return_(*)(Args_...)>::Type<Result_, Fn_>::reset() {
			auto value{get()};
			for(auto& read_fn: read_fns_) {
				read_fn(value);
			}
		}
	}
	
	namespace make_system {
		template<typename Result_, auto Fn_>
		template<typename... Ts>
		SFn<Result_, Fn_>::SFn(Ts... args) : detail::make_system::SFnImpl<decltype(Fn_)>::template Type<Result_, Fn_>(std::forward<Ts>(args)...) {
		}
	}
	
	template<typename Result_, auto Fn_>
	template<typename... Ts>
	SFn<Result_, Fn_>::SFn(Ts... args) : detail::SFnImpl<decltype(Fn_)>::template Type<Result_, Fn_>(std::forward<Ts>(args)...) {
	}
}

template<typename Result_, typename Return_, typename... Args_, Return_ (* Fn_)(Args_...)>
template<size_t... Index>
std::tuple<ie::detail::SFnMakeWrap<Args_>...>
ieml::Decode<char, ie::make_system::SFn<Result_, Fn_> >::decode_args(
	ieml::ListView const& list, std::index_sequence<Index...>
) {
	return std::make_tuple(
		std::forward<ie::detail::SFnMakeWrap<Args_> >(
			list.at(Index).except().as<ie::detail::SFnMakeWrap<Args_> >().except()
		)...
	);
}

template<typename Result_, typename Return_, typename... Args_, Return_ (* Fn_)(Args_...)>
orl::Option<ie::make_system::SFn<Result_, Fn_> >
ieml::Decode<char, ie::make_system::SFn<Result_, Fn_> >::decode(const ieml::Node& node) {
	auto list{node.get_list_view().except()};
	return std::apply([&](ie::detail::SFnMakeWrap<Args_>&& ... args) {
		return ie::make_system::SFn<Result_, Fn_>{
			std::forward<ie::detail::SFnMakeWrap<Args_> >(args)...
		};
	}, decode_args(list, std::index_sequence_for<Args_...>()));
}
