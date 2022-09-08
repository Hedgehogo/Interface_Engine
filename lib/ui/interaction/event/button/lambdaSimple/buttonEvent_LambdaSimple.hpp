#pragma once
#include "../simple/buttonEventSimple.hpp"

namespace ui {
	class ButtonEvent_LambdaSimple : public ButtonEvent_Simple {
	protected:
		void (*startPressedLambda)    (sf::Vector2i mousePosition);
		
		void (*stopPressedLambda)     (sf::Vector2i mousePosition);
		
		void (*whilePressedLambda)    (sf::Vector2i mousePosition);
		
		void (*whileNotPressedLambda) (sf::Vector2i mousePosition);

        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;

    public:
		explicit ButtonEvent_LambdaSimple(void (*startPressedLambda)(sf::Vector2i mousePosition), void (*whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {}, void (*stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {}, void (*whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {});

		ButtonEvent_LambdaSimple* copy() override;
	};

}
