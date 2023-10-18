//included into sConvert_to_bool_equals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolGreaterOrEquals<T>::SConvertToBoolGreaterOrEquals(PISValue<T> from_value, T compared) :
		BaseSConvertToBoolComparison<T>(from_value, convert(from_value->get_value(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolGreaterOrEquals<T>::convert(T from_value, T compared) {
		return from_value >= compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolGreaterOrEquals<T> >::decode_pointer(const YAML::Node& node, SConvertToBoolGreaterOrEquals<T>*& sConvert_to_bool_greater_or_equals) {
		sConvert_to_bool_greater_or_equals = new SConvertToBoolGreaterOrEquals<T>{
			get_s_value<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
