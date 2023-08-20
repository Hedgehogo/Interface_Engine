#include "iLayoutWithObjectsArray.hpp"

namespace ui {
	void ILayoutWithObjectsArray::setPosition(sf::Vector2f position) {
		ILayoutWithObjectsArray::move(position - layoutGetData().position);
	}
	
	void ILayoutWithObjectsArray::move(sf::Vector2f position) {
		layoutGetData().move(position);
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			getObjectAt(i).move(position);
		}
	}
	
	void ILayoutWithObjectsArray::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
	}
	
	sf::Vector2f ILayoutWithObjectsArray::getMinSize() const {
		sf::Vector2f minSize{0, 0};
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			minSize = max(minSize, getObjectAt(i).getMinSize());
		}
		return minSize;
	}
	
	sf::Vector2f ILayoutWithObjectsArray::getNormalSize() const {
		sf::Vector2f normalSize{0, 0};
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			normalSize = max(normalSize, getObjectAt(i).getNormalSize());
		}
		return normalSize;
	}
	
	void ILayoutWithObjectsArray::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			getObjectAt(i).drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
	}