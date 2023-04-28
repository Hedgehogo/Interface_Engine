//included into sConvertToBoolEquals.hpp

namespace ui {
	template<typename T>
	SConvertToBoolLessOrEquals<T>::SConvertToBoolLessOrEquals(PISValue<T> fromValue, T compared) : BaseSConvertToBoolComparison<T>(fromValue, convert(fromValue->getValue(), compared), compared) {
	}
	
	template<typename T>
	bool SConvertToBoolLessOrEquals<T>::convert(T fromValue, T compared) {
		return fromValue <= compared;
	}
	
	template<typename T>
	bool convertPointer(const YAML::Node &node, SConvertToBoolLessOrEquals<T> *&sConvertToBoolLessOrEquals) {
		sConvertToBoolLessOrEquals = new SConvertToBoolLessOrEquals<T>{
			getSValue<ISValue<T>>(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
	
	template<typename T>
	bool DecodePointer<SConvertToBoolLessOrEquals<T>>::decodePointer(const YAML::Node &node, SConvertToBoolLessOrEquals<T> *&sConvertToBoolLessOrEquals) {
		sConvertToBoolLessOrEquals = new SConvertToBoolLessOrEquals<T>{
			getSValue<ISValue<T>>(node["value"]),
			node["compared"].as<T>()
		};
		
		return true;
	}
}
