#include "IComponentBackground.hpp"

namespace ie {
	void IComponentBackground::setPosition(sf::Vector2f position) {
		IComponentLayout::setPosition(position);
	}
	
	void IComponentBackground::move(sf::Vector2f position) {
		IComponentLayout::move(position);
	}
	
	void IComponentBackground::setSize(sf::Vector2f size) {
		IComponentLayout::setSize(size);
	}
	
	void IComponentBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getBackground().resize(size, position);
	}
	
	sf::Vector2f IComponentBackground::getMinSize() const {
		return getBackground().getMinSize();
	}
	
	sf::Vector2f IComponentBackground::getNormalSize() const {
		return getBackground().getNormalSize();
	}
	
	void IComponentBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		getBackground().drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
}