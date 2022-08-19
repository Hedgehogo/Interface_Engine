#pragma once
#include "../buttonEvent.hpp"

namespace ui {
	class ButtonEvent_LambdaSimple : public ButtonEvent {
	protected:
		void (*startPressed)(sf::Vector2i mousePosition);
		
		void (*stopPressed )(sf::Vector2i mousePosition);
		
		void (*whilePressed)(sf::Vector2i mousePosition);
		
		void (*whileNotPressed  )(sf::Vector2i mousePosition);
	
	public:
		explicit ButtonEvent_LambdaSimple(void (*startPressed)(sf::Vector2i mousePosition), void (*whilePressed )(sf::Vector2i mousePosition) = [](sf::Vector2i) {}, void (*stopPressed)(sf::Vector2i mousePosition) = [](sf::Vector2i) {}, void (*whileNotPressed  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {});
		
		void update(sf::Vector2i mousePosition, bool press) override;
		
		ButtonEvent_LambdaSimple* copy() override;
	};

}
