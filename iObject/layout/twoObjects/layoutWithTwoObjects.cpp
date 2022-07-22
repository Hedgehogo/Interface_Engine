#include "layoutWithTwoObjects.h"

namespace ui {
	LayoutWithTwoObjects::LayoutWithTwoObjects(IScalable *firstObject, IScalable *secondObject) : firstObject(firstObject), secondObject(secondObject) {}
	
	void LayoutWithTwoObjects::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		firstObject->init(renderTarget, interactionStack, interactionManager, panelManager);
		secondObject->init(renderTarget, interactionStack, interactionManager, panelManager);
	}
	
	LayoutWithTwoObjects::~LayoutWithTwoObjects() {
		delete firstObject;
		delete secondObject;
	}
	
	void LayoutWithTwoObjects::draw() {
		secondObject->draw();
		firstObject->draw();
	}
	
	void LayoutWithTwoObjects::update() {
		firstObject->update();
		secondObject->update();
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