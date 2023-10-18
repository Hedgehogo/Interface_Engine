//included into sRange_value.hpp

namespace ie {
	template<typename T>
	SRangeValue<T>::SRangeValue(T value) : SValue<T>(value), upper(std::numeric_limits<T>::max()), lower(std::numeric_limits<T>::lowest()) {
	}
	
	template<typename T>
	T SRangeValue<T>::get_upper() {
		return upper;
	}
	
	template<typename T>
	T SRangeValue<T>::get_lower() {
		return lower;
	}
	
	template<typename T>
	void SRangeValue<T>::set_upper(const T& upper) {
		this->upper = std::min(this->upper, upper);
	}
	
	template<typename T>
	void SRangeValue<T>::set_lower(const T& lower) {
		this->lower = std::max(this->lower, lower);
	}
	
	template<typename T>
	void SRangeValue<T>::set_bounds(T lower, T upper) {
		set_upper(upper);
		set_lower(lower);
	}
	
	template<typename T>
	void SRangeValue<T>::set_value(const T& value) {
		this->value = std::clamp(value, lower, upper);
		for(const auto& set: this->setters)
			set(this->value);
	}
	
	template<typename T>
	bool DecodePointer<SRangeValue<T> >::decode_pointer(const YAML::Node& node, SRangeValue<T>*& sRange_value) {
		sRange_value = new SRangeValue<T>{conv_def<T>(node["value"], {})};
		return true;
	}
}