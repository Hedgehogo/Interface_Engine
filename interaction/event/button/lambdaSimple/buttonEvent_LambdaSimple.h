#pragma once
#include "../buttonEvent.h"

namespace ui {
	class ButtonEvent_LambdaSimple : public ButtonEvent {
	protected:
		void (*startPressed)(sf::Vector2i windowPosition);
		
		void (*stopPressed )(sf::Vector2i windowPosition);
		
		void (*whilePressed)(sf::Vector2i windowPosition);
		
		void (*whileNotPressed  )(sf::Vector2i windowPosition);
	
	public:
		explicit ButtonEvent_LambdaSimple(void (*startPressed)(sf::Vector2i windowPosition), void (*whilePressed )(sf::Vector2i windowPosition) = [](sf::Vector2i) {}, void (*stopPressed)(sf::Vector2i windowPosition) = [](sf::Vector2i) {}, void (*whileNotPressed  )(sf::Vector2i windowPosition) = [](sf::Vector2i) {});
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		ButtonEvent_LambdaSimple* copy() override;
	};
}
