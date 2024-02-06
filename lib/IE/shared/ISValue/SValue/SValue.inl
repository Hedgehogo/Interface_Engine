//included into SValue.hpp

namespace ie::make_system {
	template<typename T_>
	SValue<T_>::SValue(T_ data) : data(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SValue<T_>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SValue<T_>{std::move(*this), dyn_buffer}};
	}
}

template<typename T_>
orl::Option<ie::make_system::SValue<T_> >
ieml::Decode<char, ie::make_system::SValue<T_> >::decode(const ieml::Node& node) {
	return {{node.as<T_>().except()}};
}

namespace ie {
	template<typename T_>
	SValue<T_>::SValue(Make&& make, DynBuffer&) : data_(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SValue<T_>::SValue(T_ data) : data_(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	T_ SValue<T_>::get() const {
		return data_;
	}
	
	template<typename T_>
	void SValue<T_>::set(T_ value) {
		data_ = std::move(value);
		for(auto& read_fn : read_fns_) {
			read_fn(data_);
		}
	}
	
	template<typename T_>
	auto SValue<T_>::add_read_fn(SValue::ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	template<typename T_>
	bool SValue<T_>::delete_read_fn(SValue::ReadFn& read_fn) {
		auto result{std::find_if(read_fns_.cbegin(), read_fns_.cend(), [&](ReadFn const& item) {
			return &item == &read_fn;
		})};
		if(result != read_fns_.cend()) {
			read_fns_.erase(result);
			return true;
		}
		return false;
	}
}
