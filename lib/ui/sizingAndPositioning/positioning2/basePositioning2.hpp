#pragma once
#include "../../enums/location2/location2.hpp"
#include "../positioning/positioning.hpp"
#include "../positioning/internal/parent/internalPositioning.hpp"
#include "../positioning/internal/target/internalTargetPositioning.hpp"
#include "../positioning/match/parent/matchPositioning.hpp"
#include "../positioning/match/sides/matchSidesPositioning.hpp"
#include "../positioning/match/target/matchTargetPositioning.hpp"
#include "../positioning/lambda/lambdaPositioning.hpp"

namespace ui {
	class BasePositioning2 {
	public:
		virtual ~BasePositioning2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual BasePositioning2* copy() = 0;
		
		static BasePositioning2* createFromYaml(const YAML::Node &node);
	};
	
	Positioning* createPosition(float coefficient, float offset, bool relativeTarget = false);
	
	Positioning* createPosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
}
