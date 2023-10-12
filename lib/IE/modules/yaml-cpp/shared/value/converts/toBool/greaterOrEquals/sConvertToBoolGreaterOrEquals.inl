//included into sConvertToBoolEquals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolGreaterOrEquals<T>::SConvertToBoolGreaterOrEquals(PISValue<T> fromValue, T compared) :
		BaseSConvertToBoolComparison<T>(fromValue, convert(fromValue->getValue(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolGreaterOrEquals<T>::convert(T fromValue, T compared) {
		return fromValue >= compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolGreaterOrEquals<T> >::decodePointer(const YAML::Node& node, SConvertToBoolGreaterOrEquals<T>*& sConvertToBoolGreaterOrEquals) {
		sConvertToBoolGreaterOrEquals = new SConvertToBoolGreaterOrEquals<T>{
			getSValue<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
