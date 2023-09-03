#pragma once

#include "../IPositioning2.hpp"

namespace ie {
	class LambdaPositioning2 : public virtual IPositioning2 {
	public:
		struct Make : public virtual IPositioning2::Make {
			sf::Vector2f (* findPosition)(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
			
			Make(sf::Vector2f (* findPosition)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize));
			
			LambdaPositioning2* make(Positioning2InitInfo initInfo) override;
		};
		
		LambdaPositioning2(Make&& make, Positioning2InitInfo initInfo);
		
		explicit LambdaPositioning2(sf::Vector2f (* findPosition)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize));
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		LambdaPositioning2* copy() override;
	
	protected:
		sf::Vector2f (* positioning)(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
		sf::RenderTarget* renderTarget;
	};
}
