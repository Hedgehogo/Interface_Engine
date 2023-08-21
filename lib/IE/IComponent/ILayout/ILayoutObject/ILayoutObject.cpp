#include "ILayoutObject.hpp"
#include "../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ui {
	void ILayoutObject::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
	}
	
	void ILayoutObject::move(sf::Vector2f position) {
		ILayout::move(position);
	}
	
	void ILayoutObject::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
	}
	
	void ILayoutObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getObject().resize(size, position);
	}
	
	bool ILayoutObject::updateInteractions(sf::Vector2f mousePosition) {
		return getObject().updateInteractions(mousePosition);
	}
	
	sf::Vector2f ILayoutObject::getMinSize() const {
		return getObject().getMinSize();
	}
	
	sf::Vector2f ILayoutObject::getNormalSize() const {
		return getObject().getNormalSize();
	}
	
	void ILayoutObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	}