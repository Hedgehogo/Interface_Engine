//included into sConvert_value.hpp

namespace ie {
	template<typename FromType, typename ToType>
	SConvertValue<FromType, ToType>::SConvertValue(PISValue<FromType> from_value, ToType default_value) : SValue<ToType>(default_value), from_value_(from_value) {
		from_value->add_setter([this](const FromType& value) {
			set_value(convert(value));
		});
	}
	
	template<typename FromType, typename ToType>
	ToType SConvertValue<FromType, ToType>::convert(FromType from_value) {
		return static_cast<ToType>(from_value);
	}
	
	template<typename FromType, typename ToType>
	void SConvertValue<FromType, ToType>::set_from_value(PISValue<FromType> from_value) {
		from_value_ = from_value;
	}
	
	template<typename FromType, typename ToType>
	void SConvertValue<FromType, ToType>::set_value(const ToType& value) {
		SValue<ToType>::set_value(value);
	}
	
	template<typename FromType, typename ToType>
	const ToType& SConvertValue<FromType, ToType>::get_value() const {
		return SValue<ToType>::get_value();
	}
	
	/*old_yaml_decode_pointer_impl
	template<typename FromType, typename ToType>
	bool DecodePointer<SConvertValue<FromType, ToType> >::decode_pointer(const YAML::Node& node, SConvertValue<FromType, ToType>*& sConvert_value) {
		sConvert_value = new SConvertValue<FromType, ToType>{
			Buffer::get<ISValue<FromType>>(node["value"]),
			conv_def(node["default-value"], ToType{})
		};
		return true;

	}
	*/
}
