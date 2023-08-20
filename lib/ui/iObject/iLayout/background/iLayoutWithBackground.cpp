#include "iLayoutWithBackground.hpp"

namespace ui {
	void ILayoutWithBackground::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
	}
	
	void ILayoutWithBackground::move(sf::Vector2f position) {
		ILayout::move(position);
	}
	
	void ILayoutWithBackground::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
	}
	
	void ILayoutWithBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getBackground().resize(size, position);
	}
	
	sf::Vector2f ILayoutWithBackground::getMinSize() const {
		return getBackground().getMinSize();
	}
	
	sf::Vector2f ILayoutWithBackground::getNormalSize() const {
		return getBackground().getNormalSize();
	}
	
	void ILayoutWithBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		getBackground().drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	}