//included into withReferenceValue.hpp

namespace ui {
	template <typename T>
	SReferenceValue<T>::SReferenceValue(T &valueReference) : valueReference(&valueReference) {}
	
	template <typename T>
	const T &SReferenceValue<T>::getValue() const {
		return *valueReference;
	}
	
	template <typename T>
	void SReferenceValue<T>::setValue(const T &value) {
		*this->valueReference = value;
	}
	
	template <typename T>
	void SReferenceValue<T>::setReference(T &valueReference) {
		this->valueReference = &valueReference;
	}
}