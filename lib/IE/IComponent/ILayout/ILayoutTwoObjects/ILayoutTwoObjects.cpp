#include "ILayoutTwoObjects.hpp"
#include "../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ui {
	std::size_t ILayoutTwoObjects::getArraySize() const {
		return 2;
	}
	
	IScalable& ILayoutTwoObjects::getObjectAt(std::size_t index) {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(std::string("ILayoutWithTwoObjects::getObjectAt: __n (which is ") + std::to_string(index) + std::string(") >= _Nm (which is 2)"));
	}
	
	const IScalable& ILayoutTwoObjects::getObjectAt(std::size_t index) const {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(std::string("ILayoutWithTwoObjects::getObjectAt: __n (which is ") + std::to_string(index) + std::string(") >= _Nm (which is 2)"));
	}
	
	sf::Vector2f ILayoutTwoObjects::getMinSize() const {
		return max(getFirstObject().getMinSize(), getSecondObject().getMinSize());
	}
	
	sf::Vector2f ILayoutTwoObjects::getNormalSize() const {
		return max(getFirstObject().getNormalSize(), getSecondObject().getNormalSize());
	}
	
	void ILayoutTwoObjects::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getFirstObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		getSecondObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}