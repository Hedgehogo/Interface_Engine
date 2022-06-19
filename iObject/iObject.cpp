#include "iObject.h"

void ui::IObject::initObject(IObject *object, sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) {
	if(object != nullptr) {
		object->init(window, interactionStack, interactionManager, parent, overlayStack);
	}
}
