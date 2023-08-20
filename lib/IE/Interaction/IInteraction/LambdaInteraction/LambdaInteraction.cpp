#include "LambdaInteraction.hpp"

namespace ui {
	LambdaInteraction::LambdaInteraction(void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition)) :
		startPointing(startPointing), finishPointing(finishPointing) {
	}
	
	void LambdaInteraction::start(sf::Vector2i mousePosition) {
		startPointing(mousePosition);
	}
	
	void LambdaInteraction::finish(sf::Vector2i mousePosition) {
		finishPointing(mousePosition);
	}
}

