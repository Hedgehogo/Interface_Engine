#include "mouseLambdaInteraction.h"

ui::MouseLambdaInteraction::MouseLambdaInteraction(ui::ButtonEvent *leftMouseButton, ui::ButtonEvent *rightMouseButton, void ( *startPointing)(sf::Vector2i mousePosition), void (*finishPointing)(sf::Vector2i mousePosition)) :
	MouseInteraction(leftMouseButton, rightMouseButton), LambdaInteraction(startPointing, finishPointing) {}

ui::MouseLambdaInteraction::~MouseLambdaInteraction() {
	delete leftMouseButton;
	delete rightMouseButton;
}

ui::MouseLambdaInteraction *ui::MouseLambdaInteraction::copy() {
	return new MouseLambdaInteraction{leftMouseButton->copy(), rightMouseButton->copy(), startPointing, finishPointing};
}
