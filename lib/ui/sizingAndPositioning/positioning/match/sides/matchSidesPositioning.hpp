#pragma once
#include "../../positioning.hpp"
#include "../../../../enums/location/location.hpp"

namespace ui {
	class MatchSidesPositioning : public Positioning {
	protected:
		Location parentSide;
		Location objectSide;
		float offset;
	
	public:
		MatchSidesPositioning(Location parentSide, Location objectSide, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float) override;
		
		MatchSidesPositioning* copy() override;
		
		static MatchSidesPositioning* createFromYaml(const YAML::Node &node);
	};
	
	Positioning* createPosition(Location parentSide, Location objectSide, float offset);
}