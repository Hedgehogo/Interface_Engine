#include "LambdaKeyEvent.hpp"

namespace ui {
	LambdaKeyEvent::LambdaKeyEvent(
		void (* startPressedLambda)(sf::Vector2i),
		void (* whilePressedLambda)(sf::Vector2i),
		void (* stopPressedLambda)(sf::Vector2i),
		void (* whileNotPressedLambda)(sf::Vector2i)
	) :
		startPressedLambda(startPressedLambda),
		whilePressedLambda(whilePressedLambda),
		stopPressedLambda(stopPressedLambda),
		whileNotPressedLambda(whileNotPressedLambda) {
	}
	
	void LambdaKeyEvent::startPressed() {
		startPressedLambda(mousePosition);
	}
	
	void LambdaKeyEvent::stopPressed() {
		stopPressedLambda(mousePosition);
	}
	
	void LambdaKeyEvent::whilePressed() {
		whilePressedLambda(mousePosition);
	}
	
	void LambdaKeyEvent::whileNotPressed() {
		whileNotPressedLambda(mousePosition);
	}
	
	LambdaKeyEvent* LambdaKeyEvent::copy() {
		return new LambdaKeyEvent{*this};
	}
}

