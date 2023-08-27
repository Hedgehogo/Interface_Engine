#include "ILayoutObjectsArray.hpp"

namespace ie {
	void ILayoutObjectsArray::setPosition(sf::Vector2f position) {
		ILayoutObjectsArray::move(position - layoutGetData().position);
	}
	
	void ILayoutObjectsArray::move(sf::Vector2f position) {
		layoutGetData().move(position);
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			getObjectAt(i).move(position);
		}
	}
	
	void ILayoutObjectsArray::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
	}
	
	sf::Vector2f ILayoutObjectsArray::getMinSize() const {
		sf::Vector2f minSize{0, 0};
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			minSize = max(minSize, getObjectAt(i).getMinSize());
		}
		return minSize;
	}
	
	sf::Vector2f ILayoutObjectsArray::getNormalSize() const {
		sf::Vector2f normalSize{0, 0};
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			normalSize = max(normalSize, getObjectAt(i).getNormalSize());
		}
		return normalSize;
	}
	
	void ILayoutObjectsArray::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(std::size_t i = 0; i < getArraySize(); ++i) {
			getObjectAt(i).drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
	}