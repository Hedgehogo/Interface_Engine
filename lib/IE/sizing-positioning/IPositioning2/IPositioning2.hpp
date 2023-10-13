#pragma once

#include "IE/enums/Location2/Location2.hpp"
#include "../IPositioning/IPositioning.hpp"
#include "../IPositioning/InternalPositioning/InternalPositioning.hpp"
#include "../IPositioning/InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../IPositioning/MatchPositioning/MatchPositioning.hpp"
#include "../IPositioning/MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../IPositioning/MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"
#include "Positioning2initInfo/Positioning2InitInfo.hpp"

namespace ie {
	class IPositioning2 {
	public:
		struct Make {
			virtual IPositioning2* make(Positioning2InitInfo initInfo) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IPositioning2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize);
		
		virtual IPositioning2* copy() = 0;
	};
}