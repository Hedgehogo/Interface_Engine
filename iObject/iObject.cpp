#include "iObject.h"

void ui::IObject::initObject(IObject *object, sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	if(object != nullptr) {
		object->init(window, interactionStack, interactionManager, panelManager);
	}
}

void ui::IObject::setPosition(sf::Vector2f position) {
	resize(getSize(), position);
}

void ui::IObject::move(sf::Vector2f position) {
	resize(getSize(), getPosition() + position);
}

void ui::IObject::setSize(sf::Vector2f size) {
	resize(size, getPosition());
}
