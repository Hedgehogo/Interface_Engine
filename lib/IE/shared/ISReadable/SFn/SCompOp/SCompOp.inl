//included into SBoolOp.hpp

namespace ie::detail {
	template<typename T_>
	bool SCompOp<T_>::equal(T_ first, T_ second) {
		return first == second;
	}
	
	template<typename T_>
	bool SCompOp<T_>::not_equal(T_ first, T_ second) {
		return first != second;
	}
	
	template<typename T_>
	bool SCompOp<T_>::less(T_ first, T_ second) {
		return first < second;
	}
	
	template<typename T_>
	bool SCompOp<T_>::greater(T_ first, T_ second) {
		return first > second;
	}
	
	template<typename T_>
	bool SCompOp<T_>::less_or_equal(T_ first, T_ second) {
		return first <= second;
	}
	
	template<typename T_>
	bool SCompOp<T_>::greater_or_equal(T_ first, T_ second) {
		return first >= second;
	}
}
