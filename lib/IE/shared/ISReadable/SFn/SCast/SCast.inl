//included into SCast.hpp

namespace ie::detail {
	template<typename From_, typename To_>
	To_ SCast<From_, To_>::checked(From_ value) {
		constexpr auto to_max = std::numeric_limits<To_>::max();
		constexpr auto from_max = std::numeric_limits<From_>::max();
		constexpr auto to_min = std::numeric_limits<To_>::lowest();
		constexpr auto from_min = std::numeric_limits<From_>::lowest();
		if constexpr(from_max > to_max) {
			if(value > to_max) {
				return to_max;
			}
		}
		if constexpr(from_min < to_min) {
			if(value < to_min) {
				return to_min;
			}
		}
		return static_cast<To_>(value);
	}
	
	template<typename To_>
	To_ SFloatCast<To_>::floor(float value) {
		return SCast<float, To_>::checked(std::floor(value));
	}
	
	template<typename To_>
	To_ SFloatCast<To_>::ceil(float value) {
		return SCast<float, To_>::checked(std::ceil(value));
	}
	
	template<typename To_>
	To_ SFloatCast<To_>::round(float value) {
		return SCast<float, To_>::checked(std::round(value));
	}
}
