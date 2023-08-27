//included into sConvertToBoolEquals.hpp

namespace ie {
	template<typename T>
	SConvertToBoolGreater<T>::SConvertToBoolGreater(PISValue<T> fromValue, T compared) :
		BaseSConvertToBoolComparison<T>(fromValue, convert(fromValue->getValue(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolGreater<T>::convert(T fromValue, T compared) {
		return fromValue > compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolGreater<T> >::decodePointer(const YAML::Node& node, SConvertToBoolGreater<T>*& sConvertToBoolGreater) {
		sConvertToBoolGreater = new SConvertToBoolGreater<T>{
			getSValue<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
