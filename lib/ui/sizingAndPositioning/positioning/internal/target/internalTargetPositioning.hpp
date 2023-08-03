#pragma once

#include "../../iPositioning.hpp"

namespace ui {
	class InternalTargetPositioning : public IPositioning {
	public:
		explicit InternalTargetPositioning(float coefficient, float offset = 0);
		
		[[nodiscard]] float getCoefficient() const;
		
		[[nodiscard]] float getOffset() const;
		
		float findPosition(float, float objectSize, float, float targetSize) override;
		
		InternalTargetPositioning* copy() override;
	
	protected:
		float coefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<InternalTargetPositioning> {
		static bool decodePointer(const YAML::Node& node, InternalTargetPositioning*& internalTargetPositioning);
	};
}
