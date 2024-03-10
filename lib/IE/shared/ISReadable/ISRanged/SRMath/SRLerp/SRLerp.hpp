#pragma once

#include "../../SRanged/SRanged.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"

namespace ie{
	template<typename T_>
	class SRLerp;
	
	namespace make_system{
		template<typename T_>
		struct SRLerp : public virtual ie::SRanged<T_>::Make{
			MakeDyn<ie::ISRanged<T_> > x;
			T_ k;
			T_ b;
			
			SRLerp(MakeDyn<ie::ISRanged<T_> > x, T_ k, T_ b);
			
			SRLerp(MakeDyn<ie::ISRanged<T_> > x, sf::Vector2<T_> a, sf::Vector2<T_> b);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
	}
	
	template<typename T_>
	class SRLerp : public SRanged<T_>{
	public:
		using Make = make_system::SRLerp<T_>;
		
		SRLerp(Make&& make, SInitInfo init_info);
		
		auto get() const -> T_ override;
		
		auto set_upper_bound(T_ upper_bound) -> void override;
		
		auto set_lower_bound(T_ lower_bound) -> void override;
		
	protected:
		SReader<ISRanged<T_>> value_;
		T_ k_;
		T_ b_;
	};
	
	using SRLerpF = SRLerp<float>;
	using SRLerpI = SRLerp<int>;
	using SRLerpS = SRLerp<size_t>;
}



template<typename T_>
struct ieml::Decode<char, ie::make_system::SRLerp<T_> > {
	static orl::Option<ie::make_system::SRLerp<T_> > decode(ieml::Node const& node);
};

#include "SRLerp.inl"