//included into SFn.hpp

namespace ie {
	namespace make_system {
		template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		SFn<Value_, Fn_>::SFn(typename ie::ToMutable<Value_>::Make make, detail::SFnMakeWrap<Args_>... args) :
			ie::ToMutable<Value_>::Make(std::move(make)), args(std::make_tuple(std::forward<detail::SFnMakeWrap<Args_> >(args)...)) {
		}
		
		template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
		rttb::Dyn SFn<Value_, Fn_>::make(DynBuffer& dyn_buffer) {
			return rttb::Dyn{ie::SFn<Value_, Fn_>{std::move(*this), dyn_buffer}};
		}
	}
	
	template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
	SFn<Value_, Fn_>::SFn(Make&& make, DynBuffer& dyn_buffer) :
		ToMutable<Value_>(static_cast<typename ToMutable<Value_>::Make&&>(make), dyn_buffer),
		args_(std::apply([&dyn_buffer, this](detail::SFnMakeWrap<Args_>&&... args) {
			return std::make_tuple(
				detail::SFnWrap<Args_>{
					dyn_buffer.get(std::move(args)),
					[this](Return_ const&) {
						this->reset();
					}
				}...
			);
		}, std::move(make.args))) {
	}

	template<typename Value_, typename Return_, typename... Args_, Return_(* Fn_)(Args_...)>
	void SFn<Value_, Fn_>::reset() {
		auto value{std::apply([&](detail::SFnWrap <Args_> const& ... args) {
			return Fn_(args.get()...);
		}, args_)};
		this->set(value);
	}
}

template<typename Value_, typename Return_, typename... Args_, Return_ (* Fn_)(Args_...)>
template<size_t... Index>
std::tuple<ie::detail::SFnMakeWrap<Args_>...>
ieml::Decode<char, ie::make_system::SFn<Value_, Fn_> >::decode_args(
	ieml::ListView const& list, std::index_sequence<Index...>
) {
	return std::make_tuple(
		std::forward<ie::detail::SFnMakeWrap<Args_> >(
			list.at(Index).except().as<ie::detail::SFnMakeWrap<Args_> >().except()
		)...
	);
}

template<typename Value_, typename Return_, typename... Args_, Return_ (* Fn_)(Args_...)>
orl::Option<ie::make_system::SFn<Value_, Fn_> >
ieml::Decode<char, ie::make_system::SFn<Value_, Fn_> >::decode(const ieml::Node& node) {
	using ValueMake = typename ie::ToMutable<Value_>::Make;
	auto result_fn = [](ValueMake make, ListView list) {
		return std::apply([&](ie::detail::SFnMakeWrap<Args_>&& ... args) {
			return ie::make_system::SFn<Value_, Fn_>{
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
