#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class InternalPositioning : public virtual IPositioning {
	public:
		explicit InternalPositioning(float coefficient, float offset = 0);
		
		float get_coefficient() const;
		
		float get_offset() const;
		
		float find_position(float parent_position, float object_size, float parent_size, float) override;
		
		InternalPositioning* copy() override;
	
	protected:
		float coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::InternalPositioning> {
	static orl::Option<ie::InternalPositioning> decode(ieml::Node const& node);
};
