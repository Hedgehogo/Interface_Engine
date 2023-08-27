#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class InternalPositioning : public IPositioning {
	public:
		explicit InternalPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] float getCoefficient() const;
		
		[[nodiscard]] float getOffset() const;
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float) override;
		
		InternalPositioning* copy() override;
	
	protected:
		float coefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<InternalPositioning> {
		static bool decodePointer(const YAML::Node& node, InternalPositioning*& internalPositioning);
	};
}
