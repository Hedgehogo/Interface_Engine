//included into sConvert_to_bool_equals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolEquals<T>::SConvertToBoolEquals(PISValue<T> from_value, T compared) :
		BaseSConvertToBoolComparison<T>(from_value, convert(from_value->get_value(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolEquals<T>::convert(T from_value, T compared) {
		return from_value == compared;
	}
	
	/*old_yaml_decode_pointer_impl
	template<typename T>
	bool DecodePointer<SConvertToBoolEquals<T> >::decode_pointer(const YAML::Node& node, SConvertToBoolEquals<T>*& sConvert_to_bool_equals) {
		sConvert_to_bool_equals = new SConvertToBoolEquals<T>{
			get_s_value<ISValue<T>>(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;

	}
	*/
}
