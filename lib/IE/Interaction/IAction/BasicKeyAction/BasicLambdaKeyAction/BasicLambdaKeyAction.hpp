#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	template<typename T>
	class BasicLambdaKeyAction;
	
	namespace make_system {
		template<typename T = std::monostate>
		struct BasicLambdaKeyAction : public BasicKeyAction<T> {
			void (* startPressedLambda)(sf::Vector2i mousePosition);
			void (* whilePressedLambda)(sf::Vector2i mousePosition);
			void (* stopPressedLambda)(sf::Vector2i mousePosition);
			void (* whileNotPressedLambda)(sf::Vector2i mousePosition);
			
			BasicLambdaKeyAction(
				void (* startPressedLambda)(sf::Vector2i mousePosition),
				void (* whilePressedLambda )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				},
				void (* stopPressedLambda)(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				},
				void (* whileNotPressedLambda  )(sf::Vector2i mousePosition) = [](sf::Vector2i) {
				}
			);
			
			ie::BasicLambdaKeyAction<T>* make(BasicActionInitInfo<T> initInfo) override;
		};
	}
	
	template<typename T = std::monostate>
	class BasicLambdaKeyAction : public BasicBaseKeyAction<T> {
	public:
		using Make = make_system::BasicLambdaKeyAction<T>;
		
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
