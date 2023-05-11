#include "layoutWithObject.hpp"
#include "../../../drawable/manager/drawManager.hpp"

namespace ui {
	LayoutWithObject::LayoutWithObject(IScalable* object) : object(object) {
	}
	
	void LayoutWithObject::init(InitInfo initInfo) {
		object->init(initInfo);
	}
	
	LayoutWithObject::~LayoutWithObject() {
		delete object;
	}
	
	void LayoutWithObject::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
		object->resize(size, position);
	}
	
	bool LayoutWithObject::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayoutWithObject::getMinSize() const {
		return object->getMinSize();
	}
	
	sf::Vector2f LayoutWithObject::getNormalSize() const {
		return object->getNormalSize();
	}
	
	void LayoutWithObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}