#include "IComponentTwoObjects.hpp"

namespace ie {
	sf::Vector2f IComponentTwoObjects::getMinSize() const {
		return max(getFirstObject().getMinSize(), getSecondObject().getMinSize());
	}
	
	sf::Vector2f IComponentTwoObjects::getNormalSize() const {
		return max(getFirstObject().getNormalSize(), getSecondObject().getNormalSize());
	}
	
	void IComponentTwoObjects::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getFirstObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		getSecondObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}