//included into sConvert_to_bool_equals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolGreater<T>::SConvertToBoolGreater(PISValue<T> from_value, T compared) :
		BaseSConvertToBoolComparison<T>(from_value, convert(from_value->get_value(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolGreater<T>::convert(T from_value, T compared) {
		return from_value > compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolGreater<T> >::decode_pointer(const YAML::Node& node, SConvertToBoolGreater<T>*& sConvert_to_bool_greater) {
		sConvert_to_bool_greater = new SConvertToBoolGreater<T>{
			get_s_value<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
