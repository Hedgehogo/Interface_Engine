//included into with_reference_value.hpp

namespace ie {
	template<typename T>
	SReferenceValue<T>::SReferenceValue(T& value_reference) : value_reference_(&value_reference) {
	}
	
	template<typename T>
	void SReferenceValue<T>::add_setter(const typename ISValue<T>::SetterFunc& setter) {
		setters_.push_back(setter);
	}
	
	template<typename T>
	const T& SReferenceValue<T>::get_value() const {
		return *value_reference_;
	}
	
	template<typename T>
	void SReferenceValue<T>::set_value(const T& value) {
		*this->value_reference_ = value;
		for(const auto& set: setters_)
			set(value);
	}
	
	template<typename T>
	void SReferenceValue<T>::set_reference(T& value_reference) {
		this->value_reference_ = &value_reference;
		for(const auto& set: setters_)
			set(value_reference);
	}
}