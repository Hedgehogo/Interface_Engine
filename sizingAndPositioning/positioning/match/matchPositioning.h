#pragma once
#include "../positioning.h"

namespace ui {
	class MatchPositioning : public Positioning {
	protected:
		float parentCoefficient;
		float objectCoefficient;
		float offset;
		
	public:
		MatchPositioning(float parentCoefficient, float objectCoefficient, float offset = 0);
		
		void init(sf::RenderTarget &) override;
		
		float findPosition(float parentPosition, float parentSize, float objectSize) override;
		
		MatchPositioning* copy() override;
	};
	
	Positioning* createPosition(float parentCoefficient, float objectCoefficient, float offset);
}
