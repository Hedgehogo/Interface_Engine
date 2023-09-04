#include <iostream>

namespace ie {
	namespace make_system {
		template<typename T>
		BasicMouseLambdaInteraction<T>::BasicMouseLambdaInteraction(
			BoxPtr<typename ie::BasicKeyAction<T>::Make>&& leftButtonAction,
			BoxPtr<typename ie::BasicKeyAction<T>::Make>&& rightButtonAction,
			void (* startPointing)(sf::Vector2i),
			void (* finishPointing)(sf::Vector2i)
		) :
			BasicLambdaInteraction<T>::Make(std::move(startPointing), std::move(finishPointing)),
			leftButtonAction(std::move(leftButtonAction)),
			rightButtonAction(std::move(rightButtonAction)) {
		}
		
		template<typename T>
		ie::BasicMouseLambdaInteraction<T>* BasicMouseLambdaInteraction<T>::make(BasicActionInitInfo<T> initInfo) {
			return new ie::BasicMouseLambdaInteraction<T>{std::move(*this), initInfo};
		}
	}
	
	template<typename T>
	BasicMouseLambdaInteraction<T>::BasicMouseLambdaInteraction(Make&& make, BasicActionInitInfo<T> initInfo) :
		BasicLambdaInteraction<T>({std::move(make.startPointing), std::move(make.finishPointing)}, initInfo),
		leftButtonAction(make.leftButtonAction->make(initInfo)),
		rightButtonAction(make.rightButtonAction->make(initInfo)) {
	}
	
	template<typename T>
	BasicMouseLambdaInteraction<T>::BasicMouseLambdaInteraction(
		BoxPtr<BasicKeyAction<T> >&& leftButtonAction,
		BoxPtr<BasicKeyAction<T> >&& rightButtonAction,
		void (* startPointing)(sf::Vector2i mousePosition),
		void (* finishPointing)(sf::Vector2i mousePosition)
	) :
		BasicLambdaInteraction<T>(startPointing, finishPointing),
		leftButtonAction(std::move(leftButtonAction)),
		rightButtonAction(std::move(rightButtonAction)) {
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseLambdaInteraction<T>::getLeftButtonAction() {
		return *leftButtonAction;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseLambdaInteraction<T>::getLeftButtonAction() const {
		return *leftButtonAction;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicMouseLambdaInteraction<T>::getRightButtonAction() {
		return *rightButtonAction;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicMouseLambdaInteraction<T>::getRightButtonAction() const {
		return *rightButtonAction;
	}
	
	template<typename T>
	BasicMouseLambdaInteraction<T>* BasicMouseLambdaInteraction<T>::copy() {
		return new BasicMouseLambdaInteraction<T>{*this};
	}
	
	template<typename T>
	BasicMouseLambdaInteraction<T> BasicMouseLambdaInteraction<T>::debug{
		makeBoxPtr<BasicKeyAction<T>, BasicLambdaKeyAction<T> >(
			[](sf::Vector2i) {
				std::cout << "sl";
			},
			[](sf::Vector2i) {
				std::cout << "wl";
			},
			[](sf::Vector2i) {
				std::cout << "sl";
			},
			[](sf::Vector2i) {
				std::cout << "nl";
			}
		),
		makeBoxPtr<BasicKeyAction<T>, BasicLambdaKeyAction<T> >(
			[](sf::Vector2i) {
				std::cout << "sr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "wr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "sr" << std::endl;
			},
			[](sf::Vector2i) {
				std::cout << "nr" << std::endl;
			}
		),
		[](sf::Vector2i) {
			std::cout << "sp" << std::endl;
		},
		[](sf::Vector2i) {
			std::cout << "fp" << std::endl;
		}
	};
}
