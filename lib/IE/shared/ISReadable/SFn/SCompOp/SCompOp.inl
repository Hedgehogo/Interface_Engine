//included into SBoolOp.hpp

namespace ie::detail {
	template<typename T_>
	auto SCompOp<T_>::equal(T_ first, T_ second) -> bool {
		return first == second;
	}
	
	template<typename T_>
	auto SCompOp<T_>::not_equal(T_ first, T_ second) -> bool {
		return first != second;
	}
	
	template<typename T_>
	auto SCompOp<T_>::less(T_ first, T_ second) -> bool {
		return first < second;
	}
	
	template<typename T_>
	auto SCompOp<T_>::greater(T_ first, T_ second) -> bool {
		return first > second;
	}
	
	template<typename T_>
	auto SCompOp<T_>::less_or_equal(T_ first, T_ second) -> bool {
		return first <= second;
	}
	
	template<typename T_>
	auto SCompOp<T_>::greater_or_equal(T_ first, T_ second) -> bool {
		return first >= second;
	}
}
