#include "IComponentObject.hpp"
#include "../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	void IComponentObject::setPosition(sf::Vector2f position) {
		IComponentLayout::setPosition(position);
	}
	
	void IComponentObject::move(sf::Vector2f position) {
		IComponentLayout::move(position);
	}
	
	void IComponentObject::setSize(sf::Vector2f size) {
		IComponentLayout::setSize(size);
	}
	
	void IComponentObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getObject().resize(size, position);
	}
	
	bool IComponentObject::updateInteractions(sf::Vector2f mousePosition) {
		return getObject().updateInteractions(mousePosition);
	}
	
	sf::Vector2f IComponentObject::getMinSize() const {
		return getObject().getMinSize();
	}
	
	sf::Vector2f IComponentObject::getNormalSize() const {
		return getObject().getNormalSize();
	}
	
	void IComponentObject::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	}