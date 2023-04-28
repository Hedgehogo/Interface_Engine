//included into baseComparison.hpp

namespace ui {
	template<typename T>
	BaseSConvertToBoolComparison<T>::BaseSConvertToBoolComparison(PISValue<T> fromValue, bool defaultValue, T compared) : SConvertToBool<T>(fromValue, defaultValue), compared(compared) {
	}
	
	template<typename T>
	bool BaseSConvertToBoolComparison<T>::convert(T fromValue) {
		return convert(fromValue, compared);
	}
}
