#include "mouseLambdaInteraction.hpp"

#include <iostream>
ui::MouseLambdaInteraction ui::MouseLambdaInteraction::debug {
	new ui::ButtonEvent_LambdaSimple {
		[](sf::Vector2i) {std::cout << "sl";},
		[](sf::Vector2i) {std::cout << "wl";},
		[](sf::Vector2i) {std::cout << "sl";},
		[](sf::Vector2i) {std::cout << "nl";}
	},
	new ui::ButtonEvent_LambdaSimple {
		[](sf::Vector2i) {std::cout << "sr" << std::endl;},
		[](sf::Vector2i) {std::cout << "wr" << std::endl;},
		[](sf::Vector2i) {std::cout << "sr" << std::endl;},
		[](sf::Vector2i) {std::cout << "nr" << std::endl;}
	},
	[](sf::Vector2i) {std::cout << "sp" << std::endl;},
	[](sf::Vector2i) {std::cout << "fp" << std::endl;}
};

ui::MouseLambdaInteraction::MouseLambdaInteraction(ui::ButtonEvent *leftMouseButton, ui::ButtonEvent *rightMouseButton, void ( *startPointing)(sf::Vector2i mousePosition), void (*finishPointing)(sf::Vector2i mousePosition)) :
	MouseInteraction(leftMouseButton, rightMouseButton), LambdaInteraction(startPointing, finishPointing) {}

ui::MouseLambdaInteraction *ui::MouseLambdaInteraction::copy() {
	return new MouseLambdaInteraction{leftMouseButton->copy(), rightMouseButton->copy(), startPointing, finishPointing};
}
