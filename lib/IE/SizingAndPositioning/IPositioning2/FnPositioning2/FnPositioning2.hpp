#pragma once

#include "../IPositioning2.hpp"

namespace ie {
	class FnPositioning2 : public virtual IPositioning2 {
	public:
		using FindPositionFn = std::function<sf::Vector2f(
			sf::Vector2f parentPosition,
			sf::Vector2f objectSize,
			sf::Vector2f parentSize,
			sf::Vector2f targetSize
		)>;
		
		struct Make : public virtual IPositioning2::Make {
			FindPositionFn findPositionFn;
			
			Make(FindPositionFn findPositionFn);
			
			FnPositioning2* make(Positioning2InitInfo initInfo) override;
		};
		
		FnPositioning2(Make&& make, Positioning2InitInfo initInfo);
		
		FnPositioning2(FindPositionFn findPositionFn);
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		FnPositioning2* copy() override;
	
	protected:
		FindPositionFn findPositionFn;
		sf::RenderTarget* renderTarget;
	};
}
