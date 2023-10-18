//included into sConvert_to_bool_equals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolLess<T>::SConvertToBoolLess(PISValue<T> from_value, T compared) :
		BaseSConvertToBoolComparison<T>(from_value, convert(from_value->get_value(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolLess<T>::convert(T from_value, T compared) {
		return from_value < compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolLess<T> >::decode_pointer(const YAML::Node& node, SConvertToBoolLess<T>*& sConvert_to_bool_less) {
		sConvert_to_bool_less = new SConvertToBoolLess<T>{
			get_s_value<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
