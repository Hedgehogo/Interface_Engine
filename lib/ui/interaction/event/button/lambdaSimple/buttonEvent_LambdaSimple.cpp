#include "buttonEvent_LambdaSimple.h"

namespace ui {
	ButtonEvent_LambdaSimple::ButtonEvent_LambdaSimple(void (*startPressed)(sf::Vector2i mousePosition), void (*whilePressed )(sf::Vector2i mousePosition), void (*stopPressed)(sf::Vector2i mousePosition), void (*whileNotPressed  )(sf::Vector2i mousePosition)) :
		ButtonEvent(), startPressed(startPressed), whilePressed(whilePressed), stopPressed(stopPressed), whileNotPressed(whileNotPressed) {}
	
	void ButtonEvent_LambdaSimple::update(sf::Vector2i mousePosition, bool press) {
		if(this->pressed != press) {
			this->pressed = press;
			if(this->pressed) {
				startPressed(mousePosition);
			} else {
				stopPressed(mousePosition);
			}
		}
		if(this->pressed) {
			whilePressed(mousePosition);
		} else {
			whileNotPressed(mousePosition);
		}
	}
	
	ButtonEvent_LambdaSimple *ButtonEvent_LambdaSimple::copy() {
		ButtonEvent_LambdaSimple* buttonEventLambdaSimple{new ButtonEvent_LambdaSimple{startPressed, whilePressed, stopPressed, whileNotPressed}};
		ButtonEvent::copy(buttonEventLambdaSimple);
		return buttonEventLambdaSimple;
	}
}

