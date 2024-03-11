#pragma once

#include "../../SRanged/SRanged.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"

namespace ie{
	namespace detail {
		template<typename T_>
		struct Fluctuations{
			static auto sin(T_ const& value) -> T_;
			
			static auto cos(T_ const& value) -> T_;
		};
	}
	
	template<typename T_, T_(* Fn_)(T_ const&)>
	class SRFluctuations;
	
	namespace make_system{
		template<typename T_, T_(* Fn_)(T_ const&)>
		struct SRFluctuations : public virtual ie::SRanged<T_>::Make{
			MakeDyn<ie::ISRanged<T_> > value;
			T_ amplitude;
			T_ frequency;
			T_ phase;
			
			SRFluctuations(MakeDyn<ie::ISRanged<T_> > value, T_ amplitude = 1, T_ frequency = 1, T_ phase = 0);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
	}
	
	template<typename T_, T_(* Fn_)(T_ const&)>
	class SRFluctuations : public SRanged<T_>{
	public:
		using Make = make_system::SRFluctuations<T_, Fn_>;
		
		SRFluctuations(Make&& make, SInitInfo init_info);
		
		auto get() const -> T_ override;
		
	protected:
		SReader<ISRanged<T_>> value_;
		T_ amplitude_;
		T_ frequency_;
		T_ phase_;
	};
	
	template<typename T_>
	using SRSin = SRFluctuations<T_, detail::Fluctuations<T_>::sin>;
	template<typename T_>
	using SRCos = SRFluctuations<T_, detail::Fluctuations<T_>::cos>;
	
	using SRSinF = SRSin<float>;
	using SRSinI = SRSin<int>;
	using SRSinS = SRSin<size_t>;
	using SRCosF = SRCos<float>;
	using SRCosI = SRCos<int>;
	using SRCosS = SRCos<size_t>;
}

template<typename T_, T_(* Fn_)(T_ const&)>
struct ieml::Decode<char, ie::make_system::SRFluctuations<T_, Fn_> > {
	static orl::Option<ie::make_system::SRFluctuations<T_, Fn_> > decode(ieml::Node const& node);
};

#include "SRFluctuations.inl"