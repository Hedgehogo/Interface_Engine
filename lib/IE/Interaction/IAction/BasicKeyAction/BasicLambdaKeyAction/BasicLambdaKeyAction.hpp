#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicLambdaKeyAction : public BasicBaseKeyAction<T> {
	public:
		struct Make : public BasicKeyAction<T>::Make {
			void (* startPressedLambda)(sf::Vector2i mousePosition);
			void (* whilePressedLambda)(sf::Vector2i mousePosition);
			void (* stopPressedLambda)(sf::Vector2i mousePosition);
			void (* whileNotPressedLambda)(sf::Vector2i mousePosition);
			
			Make(
				void (* startPressedLambda)(sf::Vector2i mousePosition),
				void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				},
				void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				},
				void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				}
			);
			
			BasicLambdaKeyAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
		
		BasicLambdaKeyAction(Make&& make, BasicActionInitInfo<T> initInfo);
		
		explicit BasicLambdaKeyAction(
			void (* startPressedLambda)(sf::Vector2i mousePosition),
			void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			},
			void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
			}
		);
		
		BasicLambdaKeyAction<T>* copy() override;
	
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
	
	using LambdaKeyAction = BasicLambdaKeyAction<>;
}

#include "BasicLambdaKeyAction.inl"
