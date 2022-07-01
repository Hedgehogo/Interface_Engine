#pragma once
#include "../positioning.h"

namespace ui {
	class InternalPositioning : public Positioning {
	protected:
		float coefficient;
		float offset;
	
	public:
		InternalPositioning(float coefficient, float offset = 0);
		
		void init(sf::RenderTarget &) override;
		
		float findPosition(float parentPosition, float parentSize, float objectSize) override;
		
		InternalPositioning* copy() override;
	};
	
	Positioning* createPosition(float coefficient, float offset);
}
