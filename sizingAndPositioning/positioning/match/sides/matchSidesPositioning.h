#pragma once
#include "../../positioning.h"
#include "../../../../enums/location/location.h"

namespace ui {
	class MatchSidesPositioning : public Positioning {
	protected:
		Location parentSide;
		Location objectSide;
		float offset;
	
	public:
		MatchSidesPositioning(Location parentSide, Location objectSide, float offset = 0);
		
		void init(sf::RenderTarget &) override;
		
		float findPosition(float parentPosition, float parentSize, float objectSize) override;
		
		MatchSidesPositioning* copy() override;
	};
	
	Positioning* createPosition(Location parentSide, Location objectSide, float offset);
}
