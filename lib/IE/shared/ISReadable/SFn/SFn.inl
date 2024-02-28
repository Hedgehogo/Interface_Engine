//included into SFn.hpp

namespace ie {
	namespace make_system {
		template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
		SFn<Fn_>::SFn(typename ie::ToMutable<Value_>::Make make, detail::SFnMakeWrap<Args_>... args) :
			ie::ToMutable<Value_>::Make(std::move(make)), args(std::make_tuple(std::forward<detail::SFnMakeWrap<Args_> >(args)...)) {
		}
		
		template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
		rttb::Dyn SFn<Fn_>::make(SInitInfo init_info) {
			return rttb::Dyn{new ie::SFn<Fn_>{std::move(*this), init_info}};
		}
	}
	
	template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
	SFn<Fn_>::SFn(Make&& make, SInitInfo init_info) :
		ToMutable<Value_>(static_cast<typename ToMutable<Value_>::Make&&>(make), init_info),
		args_(std::apply([&init_info, this](detail::SFnMakeWrap<Args_>&&... args) {
			return std::make_tuple(
				detail::SFnWrap<Args_>{
					DynBuffer::get(std::move(args), init_info),
					[this](auto const&) {
						this->reset();
					}
				}...
			);
		}, std::move(make.args))) {
	}

	template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
	void SFn<Fn_>::reset() {
		auto value{std::apply([this](detail::SFnWrap <Args_> const& ... args) {
			return Fn_(static_cast<Value_ const&>(*this), args.get()...);
		}, args_)};
		this->set(value);
	}
	
	namespace detail {
		template<typename Value_, typename... SArgs_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		Return_ ToSFn<Value_(SArgs_...), Fn_>::fn(Value_ const&, SArgs_& ... args) {
			return Fn_(args.get()...);
		}
	}
}

template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
template<size_t... Index>
std::tuple<ie::detail::SFnMakeWrap<Args_>...>
ieml::Decode<char, ie::make_system::SFn<Fn_> >::decode_args(
	ieml::ListView const& list, std::index_sequence<Index...>
) {
	return std::make_tuple(
		std::forward<ie::detail::SFnMakeWrap<Args_> >(
			list.at(Index).except().as<ie::detail::SFnMakeWrap<Args_> >().except()
		)...
	);
}

template<typename Return_, typename Value_, typename... Args_, Return_(* Fn_)(Value_ const&, Args_...)>
orl::Option<ie::make_system::SFn<Fn_> >
ieml::Decode<char, ie::make_system::SFn<Fn_> >::decode(const ieml::Node& node) {
	using ValueMake = typename ie::ToMutable<Value_>::Make;
	auto result_fn = [](ValueMake make, ListView list) {
		return std::apply([&](ie::detail::SFnMakeWrap<Args_>&& ... args) {
			return ie::make_system::SFn<Fn_>{
				std::move(make),
				std::forward<ie::detail::SFnMakeWrap<Args_> >(args)...
			};
		}, decode_args(list, std::index_sequence_for<Args_...>()));
	};
	if constexpr(std::is_default_constructible_v<typename Value_::Make>) {
		auto clear_node{node.get_clear()};
		for(auto list: clear_node.get_list_view().ok_or_none()) {
			return result_fn({}, list);
		}
		auto map{clear_node.get_map_view().except()};
		return result_fn(
			map.get_as<ValueMake>("value").except().ok_or_else([] {
				return ValueMake{};
			}), map.at("args").except().get_list_view().except()
		);
	} else {
		auto map{node.get_map_view().except()};
		return result_fn(
			map.at("value").except().as<ValueMake>().except(),
			map.at("args").except().get_list_view().except()
		);
	}
}
