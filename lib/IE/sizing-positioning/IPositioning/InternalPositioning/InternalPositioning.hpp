#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class InternalPositioning : public virtual IPositioning {
	public:
		explicit InternalPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] float get_coefficient() const;
		
		[[nodiscard]] float get_offset() const;
		
		float find_position(float parent_position, float object_size, float parent_size, float) override;
		
		InternalPositioning* copy() override;
	
	protected:
		float coefficient_;
		float offset_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<InternalPositioning> {
		static bool decode_pointer(const YAML::Node& node, InternalPositioning*& internal_positioning);
	};
	*/
}
