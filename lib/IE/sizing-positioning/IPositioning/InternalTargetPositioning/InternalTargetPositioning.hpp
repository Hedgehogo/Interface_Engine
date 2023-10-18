#pragma once

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
		float coefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<InternalTargetPositioning> {
		static bool decode_pointer(const YAML::Node& node, InternalTargetPositioning*& internal_target_positioning);
	};
}
