#include "iLayoutWithTwoObjects.hpp"
#include "../../../drawable/manager/drawManager.hpp"

namespace ui {
	std::size_t ILayoutWithTwoObjects::getArraySize() const {
		return 2;
	}
	
	IScalable& ILayoutWithTwoObjects::getObjectAt(std::size_t index) {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(std::string("ILayoutWithTwoObjects::getObjectAt: __n (which is ") + std::to_string(index) + std::string(") >= _Nm (which is 2)"));
	}
	
	const IScalable& ILayoutWithTwoObjects::getObjectAt(std::size_t index) const {
		if(index == 0) {
			return getFirstObject();
		}
		if(index == 1) {
			return getSecondObject();
		}
		throw std::out_of_range(std::string("ILayoutWithTwoObjects::getObjectAt: __n (which is ") + std::to_string(index) + std::string(") >= _Nm (which is 2)"));
	}
	
	sf::Vector2f ILayoutWithTwoObjects::getMinSize() const {
		return max(getFirstObject().getMinSize(), getSecondObject().getMinSize());
	}
	
	sf::Vector2f ILayoutWithTwoObjects::getNormalSize() const {
		return max(getFirstObject().getNormalSize(), getSecondObject().getNormalSize());
	}
	
	void ILayoutWithTwoObjects::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		getFirstObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		getSecondObject().drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}