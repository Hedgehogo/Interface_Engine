#include "ILayoutBackground.hpp"

namespace ie {
	void ILayoutBackground::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
	}
	
	void ILayoutBackground::move(sf::Vector2f position) {
		ILayout::move(position);
	}
	
	void ILayoutBackground::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
	}
	
	void ILayoutBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layoutGetData().resize(size, position);
		getBackground().resize(size, position);
	}
	
	sf::Vector2f ILayoutBackground::getMinSize() const {
		return getBackground().getMinSize();
	}
	
	sf::Vector2f ILayoutBackground::getNormalSize() const {
		return getBackground().getNormalSize();
	}
	
	void ILayoutBackground::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		getBackground().drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	}