#pragma once

#include "../iSizing2.hpp"

namespace ui {
	class LambdaSizing2 : public ISizing2 {
	protected:
		void copy(LambdaSizing2* sizing2);
	
	public:
		explicit LambdaSizing2(sf::Vector2f (* findSize)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize), sf::Vector2f (* getParentMinSize)(sf::Vector2f objectMinSize));
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		LambdaSizing2* copy() override;
	
	protected:
		sf::Vector2f (* sizing)(sf::Vector2f parentSize, sf::Vector2f targetSize, sf::Vector2f normalSize);
		sf::Vector2f (* minSize)(sf::Vector2f objectMinSize);
		sf::RenderTarget* renderTarget;
		sf::Vector2f normalSize;
	};
}
