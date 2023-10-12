//included into sConvertValue.hpp

namespace ie {
	template<typename FromType, typename ToType>
	SConvertValue<FromType, ToType>::SConvertValue(PISValue<FromType> fromValue, ToType defaultValue) : SValue<ToType>(defaultValue), fromValue(fromValue) {
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
	
	template<typename FromType, typename ToType>
	bool DecodePointer<SConvertValue<FromType, ToType> >::decodePointer(const YAML::Node& node, SConvertValue<FromType, ToType>*& sConvertValue) {
		sConvertValue = new SConvertValue<FromType, ToType>{
			Buffer::get<ISValue<FromType>>(node["value"]),
			convDef(node["default-value"], ToType{})
		};
		return true;
	}
}
