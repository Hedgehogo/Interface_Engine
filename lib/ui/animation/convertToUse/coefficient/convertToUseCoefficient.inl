//included into convertToUseCoefficient.hpp

namespace ui {
	template<typename T>
	ConvertToUseCoefficient<T>::ConvertToUseCoefficient(float coefficient) : coefficient(coefficient) {}

	template<typename T>
	T ConvertToUseCoefficient<T>::convert(float value) {
		return value * coefficient;
	}


	template<typename T>
	bool convertPointer(const YAML::Node &node, ConvertToUseCoefficient<T>*& convertToUseCoefficient){
		convertToUseCoefficient = new ConvertToUseCoefficient<T>{
			convDef(node["coefficient"], 1.f)
		};
		return true;
	}
}
