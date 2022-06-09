#include "mouseInteraction.h"

namespace ui {
	MouseInteraction::MouseInteraction(ButtonEvent* leftMouseButton, ButtonEvent* rightMouseButton) :
		leftMouseButton(leftMouseButton), rightMouseButton(rightMouseButton) {}
	
	MouseInteraction::~MouseInteraction() {
		delete leftMouseButton;
		delete rightMouseButton;
	}
	
	bool MouseInteraction::update(sf::Vector2i mousePosition) {
		leftMouseButton->update(mousePosition, sf::Mouse::isButtonPressed(sf::Mouse::Left));
		rightMouseButton->update(mousePosition, sf::Mouse::isButtonPressed(sf::Mouse::Right));
		return false;
	}
}
