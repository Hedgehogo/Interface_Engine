//included into SLerp.hpp

namespace ie::detail {
	template<typename T_>
	T_ SLerp<T_>::lerp(SRanged<T_> const& to, ISRanged<T_>& from) {
		auto to_upper{to.get_upper_bound()};
		auto to_lower{to.get_lower_bound()};
		auto to_size{to_upper - to_lower};
		auto from_upper{from.get_upper_bound()};
		auto from_lower{from.get_lower_bound()};
		auto from_size{to_upper - to_lower};
		return (from.get() - from_lower) * to_size / from_size + to_lower;
	}
}
