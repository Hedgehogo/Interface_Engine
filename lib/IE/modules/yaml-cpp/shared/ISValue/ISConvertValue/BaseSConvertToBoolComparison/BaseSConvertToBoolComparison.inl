//included into base_comparison.hpp

namespace ie {
	template<typename T>
	BaseSConvertToBoolComparison<T>::BaseSConvertToBoolComparison(PISValue<T> from_value, bool default_value, T compared) : SConvertToBool<T>(from_value, default_value), compared_(compared) {
	}
	
	template<typename T>
	bool BaseSConvertToBoolComparison<T>::convert(T from_value) {
		return convert(from_value, compared_);
	}
}
