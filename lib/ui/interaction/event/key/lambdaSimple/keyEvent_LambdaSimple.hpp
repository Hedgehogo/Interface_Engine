#pragma once

#include "../simple/keyEventSimple.hpp"

namespace ui {
	class KeyEvent_LambdaSimple : public KeyEvent_Simple {
	protected:
		void (* startPressedLambda)(sf::Vector2i mousePosition);
		
		void (* stopPressedLambda)(sf::Vector2i mousePosition);
		
		void (* whilePressedLambda)(sf::Vector2i mousePosition);
		
		void (* whileNotPressedLambda)(sf::Vector2i mousePosition);
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit KeyEvent_LambdaSimple(void (* startPressedLambda)(sf::Vector2i mousePosition), void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
		}, void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
		}, void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
		});
		
		KeyEvent_LambdaSimple* copy() override;
	};
	
}
