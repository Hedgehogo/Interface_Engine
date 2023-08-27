#include <iostream>

namespace ie {
	template<typename T>
	BasicMouseLambdaInteraction<T> BasicMouseLambdaInteraction<T>::debug{
		makeBoxPtr<BasicKeyEvent<T>, BasicLambdaKeyEvent<T> >(
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
		makeBoxPtr<BasicKeyEvent<T>, BasicLambdaKeyEvent<T> >(
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
	
	template<typename T>
	BasicMouseLambdaInteraction<T>::BasicMouseLambdaInteraction(
		BoxPtr<BasicKeyEvent<T> >&& leftButtonEvent,
		BoxPtr<BasicKeyEvent<T> >&& rightButtonEvent,
		void (* startPointing)(sf::Vector2i mousePosition),
		void (* finishPointing)(sf::Vector2i mousePosition)
	) :
		BasicLambdaInteraction<T>(startPointing, finishPointing),
		leftButtonEvent(std::move(leftButtonEvent)),
		rightButtonEvent(std::move(rightButtonEvent)) {
	}
	
	template<typename T>
	BasicKeyEvent<T>& BasicMouseLambdaInteraction<T>::getLeftButtonEvent() {
		return *leftButtonEvent;
	}
	
	template<typename T>
	const BasicKeyEvent<T>& BasicMouseLambdaInteraction<T>::getLeftButtonEvent() const {
		return *leftButtonEvent;
	}
	
	template<typename T>
	BasicKeyEvent<T>& BasicMouseLambdaInteraction<T>::getRightButtonEvent() {
		return *rightButtonEvent;
	}
	
	template<typename T>
	const BasicKeyEvent<T>& BasicMouseLambdaInteraction<T>::getRightButtonEvent() const {
		return *rightButtonEvent;
	}
	
	template<typename T>
	BasicMouseLambdaInteraction<T>* BasicMouseLambdaInteraction<T>::copy() {
		return new BasicMouseLambdaInteraction<T>{*this};
	}
}
