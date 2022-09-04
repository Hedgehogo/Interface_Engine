#include "layoutWithTwoObjects.hpp"
#include "../../../drawable/manager/drawManager.hpp"

namespace ui {
	LayoutWithTwoObjects::LayoutWithTwoObjects(IScalable *firstObject, IScalable *secondObject) : firstObject(firstObject), secondObject(secondObject) {}
	
	void LayoutWithTwoObjects::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		secondObject->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		firstObject->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayoutWithTwoObjects::~LayoutWithTwoObjects() {
		delete firstObject;
		delete secondObject;
	}
	
	sf::Vector2f LayoutWithTwoObjects::getMinSize() {
		return max(firstObject->getMinSize(), secondObject->getMinSize());
	}
	
	sf::Vector2f LayoutWithTwoObjects::getNormalSize() {
		return max(firstObject->getNormalSize(), secondObject->getNormalSize());
	}
	
	void LayoutWithTwoObjects::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}