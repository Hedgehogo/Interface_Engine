#pragma once

#include "../SFn.hpp"
#include "../../ISRanged/SRanged/SRanged.hpp"

namespace ie {
	namespace detail {
		template<typename From, typename To>
		struct SCast {
			static To checked(From value);
		};
		
		template<typename To_>
		struct SFloatCast {
			static To_ floor(float value);
			
			static To_ ceil(float value);
			
			static To_ round(float value);
		};
		
		template<typename From_>
		struct SToString {
			static std::u32string to_string(From_ value);
		};
	}
	
	template<typename From, typename To>
	using BasicSCast = ToSFn<To(From&), detail::SCast<typename From::T, typename To::T>::checked>;
	
	template<typename From, typename To>
	using BasicSFloor = ToSFn<To(From&), detail::SFloatCast<typename To::T>::floor>;
	
	template<typename From, typename To>
	using BasicSCeil = ToSFn<To(From&), detail::SFloatCast<typename To::T>::ceil>;
	
	template<typename From, typename To>
	using BasicSRound = ToSFn<To(From&), detail::SFloatCast<typename To::T>::round>;
	
	template<typename From>
	using BasicSToString = ToSFn<SString(From&), detail::SToString<typename From::T>::to_string>;
	
	template<typename From, typename To>
	using SCast = BasicSCast<ISReadable<From>, SReadable<To> >;
	
	template<typename From, typename To>
	using SRCast = BasicSCast<ISRanged<From>, SRanged<To> >;
	
	template<typename To>
	using SFloor = BasicSFloor<ISFloat, SReadable<To> >;
	
	template<typename To>
	using SRFloor = BasicSFloor<ISRFloat, SRanged<To> >;
	
	template<typename To>
	using SCeil = BasicSCeil<ISFloat, SReadable<To> >;
	
	template<typename To>
	using SRCeil = BasicSCeil<ISRFloat, SRanged<To> >;
	
	template<typename To>
	using SRound = BasicSRound<ISFloat, SReadable<To> >;
	
	template<typename To>
	using SRRound = BasicSRound<ISRFloat, SRanged<To> >;
	
	template<typename From>
	using SToString = BasicSToString<ISReadable<From> >;
	
	using SCastF2I = SCast<float, int>;
	using SCastF2S = SCast<float, size_t>;
	using SCastI2F = SCast<int, float>;
	using SCastI2S = SCast<int, size_t>;
	using SCastS2F = SCast<size_t, float>;
	using SCastS2I = SCast<size_t, int>;
	
	using SRCastF2I = SRCast<float, int>;
	using SRCastF2S = SRCast<float, size_t>;
	using SRCastI2F = SRCast<int, float>;
	using SRCastI2S = SRCast<int, size_t>;
	using SRCastS2F = SRCast<size_t, float>;
	using SRCastS2I = SRCast<size_t, int>;
	
	using SFloorF = SFloor<float>;
	using SFloorI = SFloor<int>;
	using SFloorS = SFloor<size_t>;
	
	using SRFloorF = SRFloor<float>;
	using SRFloorI = SRFloor<int>;
	using SRFloorS = SRFloor<size_t>;
	
	using SCeilF = SCeil<float>;
	using SCeilI = SCeil<int>;
	using SCeilS = SCeil<size_t>;
	
	using SRCeilF = SRCeil<float>;
	using SRCeilI = SRCeil<int>;
	using SRCeilS = SRCeil<size_t>;
	
	using SRoundF = SRound<float>;
	using SRoundI = SRound<int>;
	using SRoundS = SRound<size_t>;
	
	using SRRoundF = SRRound<float>;
	using SRRoundI = SRRound<int>;
	using SRRoundS = SRRound<size_t>;
	
	using SToStringF = SToString<float>;
	using SToStringI = SToString<int>;
	using SToStringS = SToString<size_t>;
}

#include "SCast.inl"
