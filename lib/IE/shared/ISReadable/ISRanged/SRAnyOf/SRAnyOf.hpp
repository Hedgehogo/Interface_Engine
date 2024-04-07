#pragma once

#include "../SRanged/SRanged.hpp"
#include "../../../SReader/SReader.hpp"

namespace ie {
	template<typename T_>
	class SRAnyOf;
	
	namespace make_system{
		template<typename T_>
		struct SRAnyOf : public ie::SRanged<T_>::Make {
			std::vector<MakeDyn<ie::ISRanged<T_> > > values;
			
			explicit SRAnyOf(std::vector<MakeDyn<ie::ISRanged<T_> > > values);
			
			auto make(SInitInfo init_info) -> rttb::Dyn override;
		};
	}
	
	template<typename T_>
	class SRAnyOf : public SRanged<T_> {
	public:
		using Make = make_system::SRAnyOf<T_>;
		
		explicit SRAnyOf(Make&& make, SInitInfo init_info);
		
		auto set_upper_bound(T_ upper_bound) -> void override;
		
		auto set_lower_bound(T_ lower_bound) -> void override;
		
		auto set_bounds(T_ lower_bound, T_ upper_bound) -> void override;
		
	protected:
		std::vector<SReader<ISRanged<T_> > > values_;
	};
}

template<typename T_>
struct ieml::Decode<char, ie::make_system::SRAnyOf<T_> > {
	static orl::Option<ie::make_system::SRAnyOf<T_> > decode(ieml::Node const& node);
};

#include "SRAnyOf.inl"