#include "buttonEvent_LambdaSimple.h"

namespace ui {
	ButtonEvent_LambdaSimple::ButtonEvent_LambdaSimple(void (*startPressed)(sf::Vector2i windowPosition), void (*whilePressed )(sf::Vector2i windowPosition), void (*stopPressed)(sf::Vector2i windowPosition), void (*notPressed  )(sf::Vector2i windowPosition)) :
		ButtonEvent(), startPressed(startPressed), whilePressed(whilePressed), stopPressed(stopPressed), notPressed(notPressed) {}
	
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
			notPressed(mousePosition);
		}
	}
}

