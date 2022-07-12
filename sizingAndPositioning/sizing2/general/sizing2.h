#pragma once
#include "../baseSizing2.h"

namespace ui {
	class Sizing2 : public BaseSizing2 {
	protected:
		sf::RenderTarget* renderTarget;
		Sizing* horizontal;
		Sizing* vertical;
		
		void copy(Sizing2* sizing2);
		
	public:
		Sizing2(Sizing* horizontal, Sizing* vertical);
		
		Sizing2(bool relativeParent);
		
		Sizing2(sf::Vector2f constSize);
		
		Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget = false);
		
		Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition);
		
		~Sizing2() override;
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentMinSize(sf::Vector2f objectMinSize) override;
		
		Sizing2* copy() override;
	};
}
