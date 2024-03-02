#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class InternalTargetPositioning : public virtual IPositioning {
	public:
		explicit InternalTargetPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] auto get_coefficient() const -> float;
		
		[[nodiscard]] auto get_offset() const -> float;
		
		auto find_position(float, float object_size, float, float target_size) -> float override;
		
		auto copy() -> InternalTargetPositioning* override;
	
	protected:
		float coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::InternalTargetPositioning> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::InternalTargetPositioning>;
};
