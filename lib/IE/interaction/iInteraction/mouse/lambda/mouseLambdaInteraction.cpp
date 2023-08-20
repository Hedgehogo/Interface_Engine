#include "mouseLambdaInteraction.hpp"
#include <iostream>

namespace ui {
	MouseLambdaInteraction MouseLambdaInteraction::debug{
		makeBoxPtr<KeyEvent, KeyEvent_LambdaSimple>(
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
		makeBoxPtr<KeyEvent, KeyEvent_LambdaSimple>(
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
	
	MouseLambdaInteraction::MouseLambdaInteraction(BoxPtr<KeyEvent>&& leftButtonEvent, BoxPtr<KeyEvent>&& rightButtonEvent, void (* startPointing)(sf::Vector2i mousePosition), void (* finishPointing)(sf::Vector2i mousePosition)) :
		LambdaInteraction(startPointing, finishPointing), leftButtonEvent(std::move(leftButtonEvent)), rightButtonEvent(std::move(rightButtonEvent)) {
	}
	
	KeyEvent& MouseLambdaInteraction::getLeftButtonEvent() {
		return *leftButtonEvent;
	}
	
	const KeyEvent& MouseLambdaInteraction::getLeftButtonEvent() const {
		return *leftButtonEvent;
	}
	
	KeyEvent& MouseLambdaInteraction::getRightButtonEvent() {
		return *rightButtonEvent;
	}
	
	const KeyEvent& MouseLambdaInteraction::getRightButtonEvent() const {
		return *rightButtonEvent;
	}
	
	MouseLambdaInteraction* MouseLambdaInteraction::copy() {
		return new MouseLambdaInteraction{*this};
	}
}
