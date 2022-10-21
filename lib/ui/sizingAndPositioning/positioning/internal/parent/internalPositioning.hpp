#pragma once
#include "../../positioning.hpp"

namespace ui {
	class InternalPositioning : public Positioning {
	protected:
		float coefficient;
		float offset;
	public:
		explicit InternalPositioning(float coefficient, float offset = 0);

		[[nodiscard]] float getCoefficient() const;

		[[nodiscard]] float getOffset() const;

		float findPosition(float parentPosition, float objectSize, float parentSize, float) override;

		InternalPositioning* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, InternalPositioning *&internalPositioning);
}
