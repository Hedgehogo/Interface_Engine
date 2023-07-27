#pragma once

#include "../iInteraction.hpp"

namespace ui {
	class LambdaInteraction : public virtual IInteraction {
	protected:
		void (* startPointing)(sf::Vector2i mousePosition);
		
		void (* finishPointing)(sf::Vector2i mousePosition);
	
	public:
		LambdaInteraction(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition));
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	};
}