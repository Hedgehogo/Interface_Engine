#pragma once

#include "IE/component/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "../SRanged/SRanged.hpp"
#include "../../../SReader/SReader.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	namespace make_system{
		struct STime : public SRanged<float> {
		public:
			float end_time;
			MakeDyn<ISBool> start;
			orl::Option<MakeDyn<ISMBool>> end;
			bool pause_restart;
			
			STime(MakeDyn<ISBool> start, orl::Option<MakeDyn<ISMBool> > end, float end_time = std::numeric_limits<float>::max(), float data = {}, bool pause_restart = false);
			
			rttb::Dyn make(SInitInfo init_info) override;
		};
	}
	
	class STime : public SRFloat , public virtual IUpdatable{
	public:
		using Make = make_system::STime;
		
		STime(Make&& make, SInitInfo init_info);
		
		STime(STime &&) = delete;
		
		void update() override;
		
	protected:
		orl::Option<sf::Time> delta_;
		orl::Option<ISMBool&> end_;
		SReader<ISBool> start_;
		bool play_;
		sf::Clock clock_;
	};
}

template<>
struct ieml::Decode<char, ie::make_system::STime> {
	static orl::Option<ie::make_system::STime> decode(ieml::Node const& node);
};