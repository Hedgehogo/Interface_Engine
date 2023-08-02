#include "mouseInteraction.hpp"
#include "../../../enums/keyHandler/keyHandler.hpp"

namespace ui {
	IMouseInteraction::IMouseInteraction() {
	}
	
	void IMouseInteraction::update(sf::Vector2i mousePosition) {
		getLeftButtonEvent().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseLeft));
		getRightButtonEvent().update(mousePosition, KeyHandler::isKeyPressed(Key::mouseRight));
	}
}
