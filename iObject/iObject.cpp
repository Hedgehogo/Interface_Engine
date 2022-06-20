#include "iObject.h"

void ui::IObject::initObject(IObject *object, sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
	if(object != nullptr) {
		object->init(window, interactionStack, interactionManager, panelManager);
	}
}
