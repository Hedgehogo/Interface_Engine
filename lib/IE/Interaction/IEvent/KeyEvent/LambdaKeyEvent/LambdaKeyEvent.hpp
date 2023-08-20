#pragma once

#include "../BaseKeyEvent/BaseKeyEvent.hpp"

namespace ui {
	class LambdaKeyEvent : public BaseKeyEvent {
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
	
	public:
		explicit LambdaKeyEvent(
			void (* startPressedLambda)(sf::Vector2i mousePosition),
			void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			}
		);
		
		LambdaKeyEvent* copy() override;
	
	protected:
		void (* startPressedLambda)(sf::Vector2i mousePosition);
		void (* whilePressedLambda)(sf::Vector2i mousePosition);
		void (* stopPressedLambda)(sf::Vector2i mousePosition);
		void (* whileNotPressedLambda)(sf::Vector2i mousePosition);
	};
}
