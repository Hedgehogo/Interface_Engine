#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicLambdaKeyEvent : public BasicBaseKeyEvent<T> {
	public:
		explicit BasicLambdaKeyEvent(
			void (* startPressedLambda)(sf::Vector2i mousePosition),
			void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			}
		);
		
		BasicLambdaKeyEvent<T>* copy() override;
	
	protected:
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		void (* startPressedLambda)(sf::Vector2i mousePosition);
		void (* whilePressedLambda)(sf::Vector2i mousePosition);
		void (* stopPressedLambda)(sf::Vector2i mousePosition);
		void (* whileNotPressedLambda)(sf::Vector2i mousePosition);
	};
	
	using LambdaKeyEvent = BasicLambdaKeyEvent<>;
}

#include "BasicLambdaKeyEvent.inl"
