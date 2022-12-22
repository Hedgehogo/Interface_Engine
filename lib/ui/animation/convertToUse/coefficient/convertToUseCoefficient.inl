//included into convertToUseCoefficient.hpp

namespace ui {
	template<typename T>
	ConvertToUseCoefficient<T>::ConvertToUseCoefficient(float coefficient) : coefficient(coefficient) {}

	template<typename T>
	T ConvertToUseCoefficient<T>::convert(float value) {
		return value * coefficient;
	}
}
