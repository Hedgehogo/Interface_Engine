#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class InternalTargetPositioning : public virtual IPositioning {
	public:
		explicit InternalTargetPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] float get_coefficient() const;
		
		[[nodiscard]] float get_offset() const;
		
		float find_position(float, float object_size, float, float target_size) override;
		
		InternalTargetPositioning* copy() override;
	
	protected:
		float coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::InternalTargetPositioning> {
	static orl::Option<ie::InternalTargetPositioning> decode(ieml::Node const& node);
};
