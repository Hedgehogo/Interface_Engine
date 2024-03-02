//included into SCast.hpp

#include <cmath>
#include <cfenv>

namespace ie::detail {
	template<typename T_>
	struct NearbyInt;
	
	template<>
	struct NearbyInt<float> {
		template<typename T>
		constexpr static auto nearby_int(T value) -> float {
			return std::nearbyintf(value);
		}
	};
	
	template<>
	struct NearbyInt<double> {
		template<typename T>
		constexpr static auto nearby_int(T value) -> double {
			return std::nearbyint(value);
		}
	};
	
	template<>
	struct NearbyInt<long double> {
		template<typename T>
		constexpr static auto nearby_int(T value) -> long double {
			return std::nearbyintl(value);
		}
	};
	
	template<typename To_, typename From_>
	constexpr auto nearby_int(From_ value) -> To_ {
		return NearbyInt<To_>::nearby_int(std::forward<From_>(value));
	}
	
	template<typename From_, typename To_>
	auto SCast<From_, To_>::checked(From_ value) -> To_ {
		constexpr auto to_max = std::numeric_limits<To_>::max();
		constexpr auto from_max = std::numeric_limits<From_>::max();
		constexpr auto to_min = std::numeric_limits<To_>::lowest();
		constexpr auto from_min = std::numeric_limits<From_>::lowest();
		if constexpr(std::is_floating_point_v<To_> && std::numeric_limits<From_>::is_integer) {
			return nearby_int<To_>(value);
		} else if constexpr(std::is_floating_point_v<From_> && std::numeric_limits<To_>::is_integer) {
			auto last_round{std::fegetround()};
			std::fesetround(FE_TOWARDZERO);
			if(value > nearby_int<From_>(to_max)) {
				return to_max;
			}
			if(value < nearby_int<From_>(to_min)) {
				return to_min;
			}
			std::fesetround(last_round);
			return static_cast<To_>(value);
		} else {
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
	}
	
	template<typename To_>
	auto SFloatCast<To_>::floor(float value) -> To_ {
		return SCast<float, To_>::checked(std::floor(value));
	}
	
	template<typename To_>
	auto SFloatCast<To_>::ceil(float value) -> To_ {
		return SCast<float, To_>::checked(std::ceil(value));
	}
	
	template<typename To_>
	auto SFloatCast<To_>::round(float value) -> To_ {
		return SCast<float, To_>::checked(std::round(value));
	}
	
	template<typename From_>
	auto SToString<From_>::to_string(From_ value) -> std::u32string {
		return ie::to_utf32(std::to_string(value));
	}
}
