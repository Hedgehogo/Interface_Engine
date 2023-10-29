//included into sRange_value.hpp

namespace ie {
	template<typename T>
	SRangeValue<T>::SRangeValue(T value) : SValue<T>(value), upper_(std::numeric_limits<T>::max()), lower_(std::numeric_limits<T>::lowest()) {
	}
	
	template<typename T>
	T SRangeValue<T>::get_upper() {
		return upper_;
	}
	
	template<typename T>
	T SRangeValue<T>::get_lower() {
		return lower_;
	}
	
	template<typename T>
	void SRangeValue<T>::set_upper(const T& upper) {
		this->upper_ = std::min(this->upper_, upper);
	}
	
	template<typename T>
	void SRangeValue<T>::set_lower(const T& lower) {
		this->lower_ = std::max(this->lower_, lower);
	}
	
	template<typename T>
	void SRangeValue<T>::set_bounds(T lower, T upper) {
		set_upper(upper);
		set_lower(lower);
	}
	
	template<typename T>
	void SRangeValue<T>::set_value(const T& value) {
		this->value_ = std::clamp(value, lower_, upper_);
		for(const auto& set: this->setters_)
			set(this->value_);
	}
	
	/*old_yaml_decode_pointer_impl
	template<typename T>
	bool DecodePointer<SRangeValue<T> >::decode_pointer(const YAML::Node& node, SRangeValue<T>*& sRange_value) {
		sRange_value = new SRangeValue<T>{conv_def<T>(node["value"], {})};
		return true;

	}
	*/
}