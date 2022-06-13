#include "mouseInteraction.h"

namespace ui {
	MouseInteraction::MouseInteraction(ButtonEvent* leftMouseButton, ButtonEvent* rightMouseButton) :
		leftMouseButton(leftMouseButton), rightMouseButton(rightMouseButton) {}
	
	MouseInteraction::~MouseInteraction() {
		delete leftMouseButton;
		delete rightMouseButton;
	}
	
	void MouseInteraction::setLeftButtonEvent(ButtonEvent* leftMouseButton) {
		delete this->leftMouseButton;
		this->leftMouseButton = leftMouseButton->copy();
	}
	
	void MouseInteraction::setRightButtonEvent(ButtonEvent* rightMouseButton) {
		delete this->rightMouseButton;
		this->rightMouseButton = rightMouseButton->copy();
	}
	
	bool MouseInteraction::update(sf::Vector2i mousePosition) {
		leftMouseButton->update(mousePosition, sf::Mouse::isButtonPressed(sf::Mouse::Left));
		rightMouseButton->update(mousePosition, sf::Mouse::isButtonPressed(sf::Mouse::Right));
		return false;
	}
}
