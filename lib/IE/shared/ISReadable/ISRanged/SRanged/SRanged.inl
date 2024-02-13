//included into SRanged.hpp

namespace ie::make_system {
	template<typename T_>
	SRanged<T_, true>::SRanged(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SRanged<T_, true>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SRanged<T_>{std::move(*this), dyn_buffer}};
	}
	
	template<typename T_>
	SRanged<T_, false>::SRanged(T_ data) : SReadable<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SRanged<T_, false>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SRanged<T_>{std::move(*this), dyn_buffer}};
	}
	
	template<typename T_>
	SMRanged<T_, true>::ToMutable(T_ data) : SRanged<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SMRanged<T_, true>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SMRanged<T_>{std::move(*this), dyn_buffer}};
	}
	
	template<typename T_>
	SMRanged<T_, false>::ToMutable(T_ data) : SRanged<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SMRanged<T_, false>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SMRanged<T_>{std::move(*this), dyn_buffer}};
	}
}

template<typename T_>
orl::Option<ie::make_system::SRanged<T_> >
ieml::Decode<char, ie::make_system::SRanged<T_> >::decode(const ieml::Node& node) {
	return ieml::Decode<char, ie::make_system::SReadable<T_> >::decode(node).map([](auto&& value) {
		return ie::make_system::SRanged<T_>{std::move(value.data)};
	});
}

template<typename T_>
orl::Option<ie::make_system::SMRanged<T_> >
ieml::Decode<char, ie::make_system::SMRanged<T_> >::decode(const ieml::Node& node) {
	return ieml::Decode<char, ie::make_system::SRanged<T_> >::decode(node).map([](auto&& value) {
		return ie::make_system::SMRanged<T_>{std::move(value.data)};
	});
}

namespace ie {
	template<typename T_>
	SRanged<T_>::SRanged(Make&& make, DynBuffer& dyn_buffer) :
		SRanged(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SRanged<T_>::SRanged(T_ data) :
		SReadable<T_>(std::forward<T_>(data)),
		upper_bound_(std::numeric_limits<T_>::max()),
		lower_bound_(std::numeric_limits<T_>::lowest()) {
	}
	
	template<typename T_>
	T_ SRanged<T_>::get_upper_bound() {
		return upper_bound_;
	}
	
	template<typename T_>
	T_ SRanged<T_>::get_lower_bound() {
		return lower_bound_;
	}
	
	template<typename T_>
	void SRanged<T_>::set_upper_bound(T_ upper_bound) {
		if(upper_bound_ > upper_bound) {
			upper_bound_ = std::forward<T_>(upper_bound);
			if(this->data_ > upper_bound_) {
				set(upper_bound_);
			}
		}
	}
	
	template<typename T_>
	void SRanged<T_>::set_lower_bound(T_ lower_bound) {
		if(lower_bound_ < lower_bound) {
			lower_bound_ = std::forward<T_>(lower_bound);
			if(this->data_ < lower_bound_) {
				set(lower_bound_);
			}
		}
	}
	
	template<typename T_>
	void SRanged<T_>::set_bounds(T_ lower_bound, T_ upper_bound) {
		if(upper_bound_ > upper_bound && lower_bound_ < lower_bound) {
			upper_bound_ = std::forward<T_>(upper_bound);
			lower_bound_ = std::forward<T_>(lower_bound);
			if(this->data_ > upper_bound_) {
				set(upper_bound_);
			} else if(this->data_ < lower_bound_) {
				set(lower_bound_);
			}
		} else {
			set_upper_bound(upper_bound);
			set_lower_bound(lower_bound);
		}
	}
	
	template<typename T_>
	void SRanged<T_>::reset() {
		auto value{this->get()};
		for(auto& read_fn: this->read_fns_) {
			read_fn(value);
		}
	}
	
	template<typename T_>
	void SRanged<T_>::set(T_ value) {
		if(value > upper_bound_) {
			this->data_ = upper_bound_;
		} else if(value < lower_bound_) {
			this->data_ = lower_bound_;
		} else {
			this->data_ = std::forward<T_>(value);
		}
		reset();
	}
	
	template<typename T_>
	SMRanged<T_>::ToMutable(Make&& make, DynBuffer& dyn_buffer) :
		SRanged<T_>(std::forward<T_>(make.data)) {
	}
	
	template<typename T_>
	SMRanged<T_>::ToMutable(T_ data) :
		SRanged<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	void SMRanged<T_>::set(T_ value) {
		SRanged<T_>::set(std::forward<T_>(value));
	}
	
	template<typename T_>
	bool Determine<make_system::SMRanged<T_> >::determine(ieml::Node const& node) {
		return node.is_raw();
	}
}
