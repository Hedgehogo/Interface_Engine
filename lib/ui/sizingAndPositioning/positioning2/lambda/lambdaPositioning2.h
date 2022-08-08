#pragma once
#include "../basePositioning2.h"

namespace ui {
	class LambdaPositioning2 : public BasePositioning2 {
	protected:
		sf::Vector2f (*positioning)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize);
		sf::RenderTarget* renderTarget;
		
		void copy(LambdaPositioning2* lambdaPositioning2);
	
	public:
		explicit LambdaPositioning2(sf::Vector2f (*findPosition)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize));
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		LambdaPositioning2* copy() override;
	};
}
