//included into SReadable.hpp

namespace ie::make_system {
	template<typename T_>
	SReadable<T_>::SReadable(T_ data) : data(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SReadable<T_>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SReadable<T_>{std::move(*this), dyn_buffer}};
	}
	
	template<typename T_>
	SMutable<T_>::ToMutable(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SMutable<T_>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SMutable<T_>{std::move(*this), dyn_buffer}};
	}
}

template<typename T_>
orl::Option<ie::make_system::SReadable<T_> >
ieml::Decode<char, ie::make_system::SReadable<T_> >::decode(const ieml::Node& node) {
	return {{node.as<T_>().except()}};
}

template<typename T_>
orl::Option<ie::make_system::SMutable<T_> >
ieml::Decode<char, ie::make_system::SMutable<T_> >::decode(const ieml::Node& node) {
	return {{node.as<T_>().except()}};
}

namespace ie {
	template<typename T_>
	SReadable<T_>::SReadable(Make&& make, DynBuffer&) : data_(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SReadable<T_>::SReadable(T_ data) : data_(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	T_ SReadable<T_>::get() const {
		return data_;
	}
	
	template<typename T_>
	auto SReadable<T_>::add_read_fn(ReadFn&& read_fn) -> ReadFn& {
		return read_fns_.emplace_back(std::move(read_fn));
	}
	
	template<typename T_>
	bool SReadable<T_>::delete_read_fn(ReadFn& read_fn) {
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
	SMutable<T_>::ToMutable(Make&& make, DynBuffer&) : SReadable<T_>(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SMutable<T_>::ToMutable(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	void SMutable<T_>::set(T_ value) {
		this->data_ = std::move(value);
		for(auto& read_fn : this->read_fns_) {
			read_fn(this->data_);
		}
	}
}
