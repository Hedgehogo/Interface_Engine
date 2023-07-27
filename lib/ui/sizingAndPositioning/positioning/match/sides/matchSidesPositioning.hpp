#pragma once

#include "../../iPositioning.hpp"
#include "../../../../enums/location/location.hpp"

namespace ui {
	class MatchSidesPositioning : public IPositioning {
	protected:
		Location parentSide;
		Location objectSide;
		float offset;
	
	public:
		MatchSidesPositioning(Location parentSide, Location objectSide, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float) override;
		
		MatchSidesPositioning* copy() override;
	};
	
	template<>
	struct DecodePointer<MatchSidesPositioning> {
		static bool decodePointer(const YAML::Node& node, MatchSidesPositioning*& matchSidesPositioning);
	};
	
	//Positioning* makePosition(Location parentSide, Location objectSide, float offset);
}
