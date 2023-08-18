#include "iLayoutWithObject.hpp"
#include "../../../drawable/manager/drawManager.hpp"

namespace ui {
	void ILayoutWithObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getObject().resize(size, position);
	}
	
	bool ILayoutWithObject::updateInteractions(sf::Vector2f mousePosition) {
		return getObject().updateInteractions(mousePosition);
	}
	
	sf::Vector2f ILayoutWithObject::getMinSize() const {
		return getObject().getMinSize();
	}
	
	sf::Vector2f ILayoutWithObject::getNormalSize() const {
		return getObject().getNormalSize();
	}
	
	void ILayoutWithObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}