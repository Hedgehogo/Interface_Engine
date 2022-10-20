#include "mouseInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"
namespace ui {
	MouseInteraction::MouseInteraction(ButtonEvent* leftMouseButton, ButtonEvent* rightMouseButton) :
		leftMouseButton(leftMouseButton), rightMouseButton(rightMouseButton) {}
	
	void MouseInteraction::setLeftButtonEvent(ButtonEvent* leftMouseButton) {
		delete this->leftMouseButton;
		this->leftMouseButton = leftMouseButton->copy();
	}
	
	void MouseInteraction::setRightButtonEvent(ButtonEvent* rightMouseButton) {
		delete this->rightMouseButton;
		this->rightMouseButton = rightMouseButton->copy();
	}
	
	bool MouseInteraction::update(sf::Vector2i mousePosition) {
		leftMouseButton->update(mousePosition, KeyHandler::isKeyPressed(Key::mouseLeft));
		rightMouseButton->update(mousePosition, KeyHandler::isKeyPressed(Key::mouseRight));
		return false;
	}
}
