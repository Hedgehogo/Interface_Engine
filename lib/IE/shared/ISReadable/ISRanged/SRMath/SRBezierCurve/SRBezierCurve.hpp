#pragma once

#include <array>
#include "../../SRanged/SRanged.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"
#include "BezierCurveException/BezierCurveException.hpp"

namespace ie {
	template<typename T_>
	class SRBezierCurve;
	
	namespace make_system {
		template<typename T_>
		struct SRBezierCurve : public ie::SRanged<T_>::Make {
			MakeDyn<ie::ISRanged<T_> > value;
			std::array<T_, 4> points;
			
			SRBezierCurve(MakeDyn<ie::ISRanged<T_> > value, std::array<T_, 4> points);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
	}
	
	template<typename T_>
	class SRBezierCurve : public SRanged<T_>{
	public:
		using Make = make_system::SRBezierCurve<T_>;
		
		SRBezierCurve(Make&& make, SInitInfo init_info);
		
		auto get() const -> T_ override;
		
		auto set_upper_bound(T_ upper_bound) -> void override;
		
		auto set_lower_bound(T_ lower_bound) -> void override;
		
		auto set_bounds(T_ lower_bound, T_ upper_bound) -> void override;
	
	protected:
		SReader<ISRanged<T_> > value_;
		std::array<T_, 4> points_;
		T_ size_;
	};
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SRBezierCurve<T_> > {
	static orl::Option<ie::make_system::SRBezierCurve<T_> > decode(ieml::Node const& node);
};

#include "SRBezierCurve.inl"