#pragma once
#include "../../enums/location2/location2.h"
#include "../positioning/positioning.h"
#include "../positioning/internal/internalPositioning.h"
#include "../positioning/match/matchPositioning.h"
#include "../positioning/match/sides/matchSidesPositioning.h"

namespace ui {
	class Positioning2 {
	protected:
		Positioning* horizontal;
		Positioning* vertical;
	
	public:
		Positioning2(Positioning* horizontal, Positioning* vertical);
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f offset = {});
		
		Positioning2(sf::Vector2f parentCoefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset);
		
		Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset = {});
		
		virtual ~Positioning2();
		
		virtual void init(sf::RenderTarget& renderTarget);
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual Positioning2* copy();
	};
}
