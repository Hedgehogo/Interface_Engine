#include "mouseLambdaInteraction.hpp"

#include <iostream>

namespace ui {
	MouseLambdaInteraction MouseLambdaInteraction::debug{
		new ButtonEvent_LambdaSimple{
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
		},
		new ButtonEvent_LambdaSimple{
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
		},
		[](sf::Vector2i) {
			std::cout << "sp" << std::endl;
		},
		[](sf::Vector2i) {
			std::cout << "fp" << std::endl;
		}
	};
	
	MouseLambdaInteraction::MouseLambdaInteraction(ButtonEvent *leftMouseButton, ButtonEvent *rightMouseButton, void ( *startPointing)(sf::Vector2i mousePosition), void (*finishPointing)(sf::Vector2i mousePosition)) :
		MouseInteraction(leftMouseButton, rightMouseButton), LambdaInteraction(startPointing, finishPointing) {
	}
	
	MouseLambdaInteraction *MouseLambdaInteraction::copy() {
		return new MouseLambdaInteraction{leftMouseButton->copy(), rightMouseButton->copy(), startPointing, finishPointing};
	}
}
