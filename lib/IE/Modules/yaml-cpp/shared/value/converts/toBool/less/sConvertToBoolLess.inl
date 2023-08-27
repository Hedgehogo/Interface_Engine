//included into sConvertToBoolEquals.hpp

namespace ui {
	template<typename T>
	SConvertToBoolLess<T>::SConvertToBoolLess(PISValue<T> fromValue, T compared) :
		BaseSConvertToBoolComparison<T>(fromValue, convert(fromValue->getValue(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolLess<T>::convert(T fromValue, T compared) {
		return fromValue < compared;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolLess<T> >::decodePointer(const YAML::Node& node, SConvertToBoolLess<T>*& sConvertToBoolLess) {
		sConvertToBoolLess = new SConvertToBoolLess<T>{
			getSValue<ISValue<T> >(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
