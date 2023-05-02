#include "layoutWithObjectsArray.hpp"

namespace ui {
	LayoutWithObjectsArray::LayoutWithObjectsArray(std::vector<IScalable*> objects) : objects(objects) {
	}
	
	void
	LayoutWithObjectsArray::init(InitInfo initInfo) {
		for(auto object: objects) {
			object->init(initInfo);
		}
	}
	
	LayoutWithObjectsArray::~LayoutWithObjectsArray() {
		for(auto object: objects) {
			delete object;
		}
	}
	
	void LayoutWithObjectsArray::move(sf::Vector2f position) {
		Layout::move(position);
		for(const auto& object: objects){
			object->move(position);
		}
	}
	
	sf::Vector2f LayoutWithObjectsArray::getMinSize() {
		sf::Vector2f minSize{0, 0};
		for(auto object: objects) {
			minSize = max(minSize, object->getMinSize());
		}
		return minSize;
	}
	
	sf::Vector2f LayoutWithObjectsArray::getNormalSize() {
		sf::Vector2f normalSize{0, 0};
		for(auto object: objects) {
			normalSize = max(normalSize, object->getNormalSize());
		}
		return normalSize;
	}
	
	uint LayoutWithObjectsArray::getArraySize() {
		return objects.size();
	}
	
	void LayoutWithObjectsArray::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto object: objects) {
			object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);;
		}
	}
}