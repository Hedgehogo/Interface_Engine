#include "layoutWithObjectsArray.h"

namespace ui {
	LayoutWithObjectsArray::LayoutWithObjectsArray(std::vector<IScalable *> objects) : objects(objects) {}
	
	void LayoutWithObjectsArray::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		for(auto object: objects) {
			object->init(renderTarget, interactionStack, interactionManager, panelManager);
		}
	}
	
	LayoutWithObjectsArray::~LayoutWithObjectsArray() {
		for(auto object: objects) {
			delete object;
		}
	}
	
	void LayoutWithObjectsArray::draw() {
		for(auto object: objects) {
			object->draw();
		}
	}
	
	void LayoutWithObjectsArray::update() {
		for(auto object: objects) {
			object->update();
		}
	}
	
	sf::Vector2f LayoutWithObjectsArray::getMinSize() {
		sf::Vector2f minSize{0, 0};
		for(auto object: objects) {
			minSize = max(minSize, object->getMinSize());
		}
		return minSize;
	}
	
	sf::Vector2f LayoutWithObjectsArray::getNormalSize() {
		sf::Vector2f normalSize{0, 0};
		for(auto object: objects) {
			normalSize = max(normalSize, object->getNormalSize());
		}
		return normalSize;
	}
	
	void LayoutWithObjectsArray::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto object: objects) {
			object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);;
		}
	}
}