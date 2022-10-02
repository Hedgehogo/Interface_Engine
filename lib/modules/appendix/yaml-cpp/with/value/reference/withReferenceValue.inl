//included into withReferenceValue.hpp

namespace ui {
	template <typename T>
	WithReferenceValue<T>::WithReferenceValue(T &valueReference) : valueReference(&valueReference) {}
	
	template <typename T>
	const T &WithReferenceValue<T>::getValue() const {
		return *valueReference;
	}
	
	template <typename T>
	void WithReferenceValue<T>::setValue(const T &value) {
		*this->valueReference = value;
	}
	
	template <typename T>
	void WithReferenceValue<T>::setReference(T &valueReference) {
		this->valueReference = &valueReference;
	}
}