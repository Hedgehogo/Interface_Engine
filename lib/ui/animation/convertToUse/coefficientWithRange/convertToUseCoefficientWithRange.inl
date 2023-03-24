//included into convertToUseCoefficientWithRange.hpp

#include <algorithm>
#include <iostream>

namespace ui {

	template<typename T>
	ConvertToUseCoefficientWithRange<T>::ConvertToUseCoefficientWithRange(float coefficient, float max, float min) : ConvertToUseCoefficient<T>(coefficient), max(max), min(min) {}

	template<typename T>
	T ConvertToUseCoefficientWithRange<T>::convert(float value) {
		return std::max(min, std::min(max, ConvertToUseCoefficient<T>::convert(value)));
	}


	template<typename T>
	bool convertPointer(const YAML::Node &node, ConvertToUseCoefficientWithRange<T>*& convertToUseCoefficientWithRange){
		convertToUseCoefficientWithRange = new ConvertToUseCoefficientWithRange<T>{
			convDef(node["coefficient"], 1.f),
			convDef(node["max"], 1.f),
			convDef(node["min"], 0.f)
		};
		return true;
	}
}
