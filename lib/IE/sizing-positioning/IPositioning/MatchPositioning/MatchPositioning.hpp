#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class MatchPositioning : public virtual IPositioning {
	public:
		MatchPositioning(float parent_coefficient, float object_coefficient, float offset = 0);
		
		float find_position(float parent_position, float object_size, float parent_size, float) override;
		
		MatchPositioning* copy() override;
	
	protected:
		float parent_coefficient_;
		float object_coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::MatchPositioning> {
	static orl::Option<ie::MatchPositioning> decode(ieml::Node const& node);
};
