#pragma once

#include "../../Enums/Location2/Location2.hpp"
#include "../positioning/iPositioning.hpp"
#include "../positioning/internal/parent/internalPositioning.hpp"
#include "../positioning/internal/target/internalTargetPositioning.hpp"
#include "../positioning/match/parent/matchPositioning.hpp"
#include "../positioning/match/sides/matchSidesPositioning.hpp"
#include "../positioning/match/target/matchTargetPositioning.hpp"
#include "../positioning/lambda/lambdaPositioning.hpp"

namespace ui {
	class IPositioning2 {
	public:
		virtual ~IPositioning2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual IPositioning2* copy() = 0;
	};
/*
	Positioning* makePosition(float coefficient, float offset, bool relativeTarget = false);
	
	Positioning* makePosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
*/
}
