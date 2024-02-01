//included into SRanged.hpp

namespace ie::make_system {
	template<typename T_>
	SRanged<T_>::SRanged(T_ data) : SValue<T_>(std::forward<T_>(data)) {
	}
	
	template<typename T_>
	rttb::Dyn SRanged<T_>::make(DynBuffer& dyn_buffer) {
		return rttb::Dyn{ie::SRanged<T_>{std::move(*this), dyn_buffer}};
	}
}

template<typename T_>
orl::Option<ie::make_system::SRanged<T_> > ieml::Decode<char, ie::make_system::SRanged<T_> >::decode(const ieml::Node& node) {
	return {{node.as<T_>().except()}};
}

namespace ie {
	template<typename T_>
	SRanged<T_>::SRanged(Make&& make, DynBuffer& dyn_buffer) :
		SValue<T_>(std::forward<T_>(make.data), dyn_buffer),
		upper_bound_(std::numeric_limits<T_>::max()),
		lower_bound_(std::numeric_limits<T_>::lowest()) {
	}
	
	template<typename T_>
	SRanged<T_>::SRanged(T_ data) :
		SValue<T_>(std::forward<T_>(data)),
		upper_bound_(std::numeric_limits<T_>::max()),
		lower_bound_(std::numeric_limits<T_>::lowest()) {
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
}
