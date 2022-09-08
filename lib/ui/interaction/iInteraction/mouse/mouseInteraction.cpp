#include "mouseInteraction.hpp"
#include "../../../enums/button/button.hpp"
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
		leftMouseButton->update(mousePosition, isKeyPressed(Key::mouseLeft));
		rightMouseButton->update(mousePosition, isKeyPressed(Key::mouseRight));
		return false;
	}
}
