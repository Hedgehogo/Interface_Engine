#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class InternalPositioning : public virtual IPositioning {
	public:
		explicit InternalPositioning(float coefficient, float offset = 0);
		
		auto get_coefficient() const -> float;
		
		auto get_offset() const -> float;
		
		auto find_position(float parent_position, float object_size, float parent_size, float) -> float override;
		
		auto copy() -> InternalPositioning* override;
	
	protected:
		float coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::InternalPositioning> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::InternalPositioning>;
};
