#pragma once

#include "../IPositioning2.hpp"

namespace ui {
	class LambdaPositioning2 : public IPositioning2 {
	public:
		explicit LambdaPositioning2(sf::Vector2f (* findPosition)(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize, sf::Vector2f targetSize));
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		LambdaPositioning2* copy() override;
	
	protected:
		sf::Vector2f (* positioning)(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
		sf::RenderTarget* renderTarget;
	};
}
