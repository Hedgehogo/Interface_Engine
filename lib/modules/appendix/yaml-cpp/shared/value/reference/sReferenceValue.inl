//included into withReferenceValue.hpp

namespace ui {
	template <typename T>
	SReferenceValue<T>::SReferenceValue(T &valueReference) : valueReference(&valueReference) {}
	
	template <typename T>
	void SReferenceValue<T>::addSetter(const typename ISValue<T>::SetterFunc& setter) {
		setters.push_back(setter);
	}
	
	template <typename T>
	const T &SReferenceValue<T>::getValue() const {
		return *valueReference;
	}
	
	template <typename T>
	void SReferenceValue<T>::setValue(const T &value) {
		*this->valueReference = value;
		for(const auto &set: setters) set(value);
	}
	
	template <typename T>
	void SReferenceValue<T>::setReference(T &valueReference) {
		this->valueReference = &valueReference;
		for(const auto &set: setters) set(valueReference);
	}
}