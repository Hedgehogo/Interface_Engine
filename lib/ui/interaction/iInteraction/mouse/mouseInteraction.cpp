#include "mouseInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
namespace ui {
	MouseInteraction::MouseInteraction(KeyEvent* leftMouseButton, KeyEvent* rightMouseButton) :
		leftMouseButton(leftMouseButton), rightMouseButton(rightMouseButton) {}
	
	void MouseInteraction::setLeftButtonEvent(KeyEvent* leftMouseButton) {
		delete this->leftMouseButton;
		this->leftMouseButton = leftMouseButton->copy();
	}
	
	void MouseInteraction::setRightButtonEvent(KeyEvent* rightMouseButton) {
		delete this->rightMouseButton;
		this->rightMouseButton = rightMouseButton->copy();
	}
	
	void MouseInteraction::update(sf::Vector2i mousePosition) {
		leftMouseButton->update(mousePosition, KeyHandler::isKeyPressed(Key::mouseLeft));
		rightMouseButton->update(mousePosition, KeyHandler::isKeyPressed(Key::mouseRight));
	}
}
