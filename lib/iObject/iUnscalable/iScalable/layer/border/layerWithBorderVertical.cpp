#include "layerWithBorderVertical.h"
#include "../../../../../interaction/interactionManager/interactionManager.h"
#include <vector>

namespace ui {
	LayerWithBorderVertical::LayerWithBorderVertical(std::vector<IScalable *> objects, std::vector<float> boundsVertical, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), boundsVertical(std::move(boundsVertical))  {
		this->boundsVertical.insert(this->boundsVertical.begin(), 0.0f);
		this->boundsVertical.push_back(1.0f);
	}
	
	LayerWithBorderVertical::LayerWithBorderVertical(std::vector<IScalable *> objects, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), boundsVertical(this->objects.size() + 1, 1.0f) {
		auto count = this->objects.size();
		for(unsigned long long i = 0; i < count; ++i) {
			boundsVertical[i] = static_cast<float>(i) / static_cast<float>(count);
		}
	}
	
	LayerWithBorderVertical::LayerWithBorderVertical(IScalable *first, IScalable *second, float bound, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray({first, second}), boundsVertical({0.f, bound, 1.f}) {}
	
	void LayerWithBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for(unsigned y = 0; y < objects.size(); ++y) {
			objectSize.y = size.y * (boundsVertical[y + 1] - boundsVertical[y]);
			objects[y]->resize(objectSize, position + coordinate);
			coordinate.y += objectSize.y;
		}
	}
	
	bool LayerWithBorderVertical::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position.y = position.y / size.y;
		
		unsigned long long i{1};
		while(position.y > boundsVertical[i]) ++i;
		return objects[i - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithBorderVertical::getMinSize() {
		sf::Vector2f minSize {0, 0};
		std::vector<sf::Vector2f> objectMinSizes(objects.size());
		for(int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSizes[i] = objects[i]->getMinSize();
		}
		
		sf::Vector2f objectMinSize;
		for (int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSize = {objectMinSizes[i].x, objectMinSizes[i].y / (boundsVertical[i + 1] - boundsVertical[i])};
			minSize = max(objectMinSize, minSize);
		}
		
		return max(minSize, this->minimumSize);
	}
	
	sf::Vector2f LayerWithBorderVertical::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<sf::Vector2f> objectNormalSizes(objects.size());
		for(int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSizes[i] = objects[i]->getNormalSize();
		}
		
		sf::Vector2f objectNormalSize;
		for (int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSize = {objectNormalSizes[i].x, objectNormalSizes[i].y / (boundsVertical[i + 1] - boundsVertical[i])};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	LayerWithBorderVertical *LayerWithBorderVertical::copy() {
		std::vector<IScalable *> newObjects(objects.size());
		for(int i = 0; i < newObjects.size(); ++i) {
			newObjects[i] = objects[i]->copy();
		}
		std::vector<float> newBounds(boundsVertical.size() - 2);
		for(int i = 0; i < newBounds.size(); ++i) {
			newBounds[i] = boundsVertical[i + 1];
		}
		LayerWithBorderVertical* layerWithBorderVertical{new LayerWithBorderVertical{newObjects, newBounds, minimumSize}};
		Layer::copy(layerWithBorderVertical);
		return layerWithBorderVertical;
	}
	
	void LayerWithBorderVertical::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto &object: objects) {
            object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
}
