#pragma once
#include "../baseSizing2.h"

namespace ui {
	class LambdaSizing2 : public BaseSizing2 {
	protected:
		sf::Vector2f (*sizing)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize);
		sf::RenderTarget* renderTarget;
		sf::Vector2f normalSize;
		
		void copy(LambdaSizing2* sizing2);
		
	public:
		explicit LambdaSizing2(sf::Vector2f (*findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize));
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		LambdaSizing2* copy() override;
	};
}
