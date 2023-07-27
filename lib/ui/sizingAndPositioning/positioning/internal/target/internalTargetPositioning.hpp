#pragma once

#include "../../iPositioning.hpp"

namespace ui {
	class InternalTargetPositioning : public IPositioning {
	protected:
		float coefficient;
		float offset;
	
	public:
		explicit InternalTargetPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] float getCoefficient() const;
		
		[[nodiscard]] float getOffset() const;
		
		float findPosition(float parentPosition, float objectSize, float, float targetSize) override;
		
		InternalTargetPositioning* copy() override;
	};
	
	template<>
	struct DecodePointer<InternalTargetPositioning> {
		static bool decodePointer(const YAML::Node& node, InternalTargetPositioning*& internalTargetPositioning);
	};
}
