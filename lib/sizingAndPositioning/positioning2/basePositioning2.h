#pragma once
#include "../../enums/location2/location2.h"
#include "../positioning/positioning.h"
#include "../positioning/internal/internalPositioning.h"
#include "../positioning/internal/target/internalTargetPositioning.h"
#include "../positioning/match/matchPositioning.h"
#include "../positioning/match/sides/matchSidesPositioning.h"
#include "../positioning/match/target/matchTargetPositioning.h"
#include "../positioning/lambda/lambdaPositioning.h"

namespace ui {
	class BasePositioning2 {
	public:
		virtual ~BasePositioning2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual BasePositioning2* copy() = 0;
	};
	
	Positioning* createPosition(float coefficient, float offset, bool relativeTarget = false);
	
	Positioning* createPosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
}
