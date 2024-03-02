//included into SReadable.hpp

namespace ie::make_system {
	template<typename T_>
	SReadable<T_, true>::SReadable(T_ data) : data(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SReadable<T_, true>::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SReadable<T_>{std::move(*this), SInitInfo{init_info}}};
	}
	
	template<typename T_>
	SReadable<T_, false>::SReadable(T_ data) : data(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SReadable<T_, false>::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SReadable<T_>{std::move(*this), SInitInfo{init_info}}};
	}
	
	template<typename T_>
	SMutable<T_, true>::ToMutable(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SMutable<T_, true>::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SMutable<T_>{std::move(*this), SInitInfo{init_info}}};
	}
	
	template<typename T_>
	SMutable<T_, false>::ToMutable(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SMutable<T_, false>::make(SInitInfo init_info) -> rttb::Dyn {
		return rttb::Dyn{ie::SMutable<T_>{std::move(*this), SInitInfo{init_info}}};
	}
}

template<typename T_>
auto ieml::Decode<char, ie::make_system::SReadable<T_> >::decode(const ieml::Node& node) -> orl::Option<ie::make_system::SReadable<T_> > {
	if constexpr(std::is_default_constructible_v<T_>) {
		auto& clear_node{node.get_clear()};
		if(clear_node.is_null()) {
			return {{}};
		}
		return {{clear_node.as<T_>().except()}};
	} else {
		return {{node.as<T_>().except()}};
	}
}

template<typename T_>
auto ieml::Decode<char, ie::make_system::SMutable<T_> >::decode(const ieml::Node& node) -> orl::Option<ie::make_system::SMutable<T_> > {
	return ieml::Decode<char, ie::make_system::SReadable<T_> >::decode(node).map([](auto&& value) {
		return ie::make_system::SMutable<T_>{std::move(value.data)};
	});
}

namespace ie {
	template<typename T_>
	SReadable<T_>::SReadable(Make&& make, SInitInfo init_info) : data_(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SReadable<T_>::SReadable(T_ data) : data_(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SReadable<T_>::get() const -> T_ {
		return data_;
	}
	
	template<typename T_>
	auto SReadable<T_>::add_read_fn(ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	template<typename T_>
	auto SReadable<T_>::delete_read_fn(ReadFn& read_fn) -> bool {
		auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
			return &item == &read_fn;
		})};
		if(result != read_fns_.cend()) {
			read_fns_.erase(result);
			return true;
		}
		return false;
	}
	
	template<typename T_>
	SMutable<T_>::ToMutable(Make&& make, SInitInfo) : SReadable<T_>(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SMutable<T_>::ToMutable(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	auto SMutable<T_>::set(T_ value) -> void {
		this->data_ = std::move(value);
		for(auto& read_fn : this->read_fns_) {
			read_fn(this->data_);
		}
	}
}
