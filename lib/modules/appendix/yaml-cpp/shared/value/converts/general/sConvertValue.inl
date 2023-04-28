//included into sConvertValue.hpp

namespace ui {
	
	template<typename FromType, typename ToType>
	SConvertValue<FromType, ToType>::SConvertValue(PISValue<FromType> fromValue, ToType defaultValue) : SValue<ToType>(defaultValue) {
		fromValue->addSetter([this](const FromType& value) {
			setValue(convert(value));
		});
	}
	
	template<typename FromType, typename ToType>
	ToType SConvertValue<FromType, ToType>::convert(FromType fromValue) {
		return static_cast<ToType>(fromValue);
	}
	
	template<typename FromType, typename ToType>
	void SConvertValue<FromType, ToType>::setFromValue(PISValue<FromType> fromValue) {
		this->fromValue = fromValue;
	}
	
	template<typename FromType, typename ToType>
	void SConvertValue<FromType, ToType>::setValue(const ToType& value) {
		SValue<ToType>::setValue(value);
	}
	
	template<typename FromType, typename ToType>
	const ToType& SConvertValue<FromType, ToType>::getValue() const {
		return SValue<ToType>::getValue();
	}
}
