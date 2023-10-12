//included into sConvertToBoolEquals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolEquals<T>::SConvertToBoolEquals(PISValue<T> fromValue, T compared) :
		BaseSConvertToBoolComparison<T>(fromValue, convert(fromValue->getValue(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolEquals<T>::convert(T fromValue, T compared) {
		return fromValue == compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolEquals<T> >::decodePointer(const YAML::Node& node, SConvertToBoolEquals<T>*& sConvertToBoolEquals) {
		sConvertToBoolEquals = new SConvertToBoolEquals<T>{
			getSValue<ISValue<T>>(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
