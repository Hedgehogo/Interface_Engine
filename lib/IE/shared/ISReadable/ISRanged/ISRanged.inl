//included into ISRanged.hpp

namespace ie {
	template<typename T_>
	auto ISRanged<T_>::set_bounds(T_ lower_bound, T_ upper_bound) -> void {
		this->set_upper_bound(upper_bound);
		this->set_lower_bound(lower_bound);
	}
}
