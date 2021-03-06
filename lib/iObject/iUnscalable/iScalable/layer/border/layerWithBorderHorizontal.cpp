#include "layerWithBorderHorizontal.h"
#include <vector>

namespace ui {
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(std::vector<IScalable *> objects, std::vector<float> bounds, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), boundsHorizontal(std::move(bounds)) {
		this->boundsHorizontal.insert(this->boundsHorizontal.begin(), 0.0f);
		this->boundsHorizontal.push_back(1.0f);
	}
	
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(std::vector<IScalable *> objects, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), boundsHorizontal(this->objects.size() + 1, 1.0f) {
		auto count = this->objects.size();
		for(unsigned long long i = 0; i < count; ++i) {
			boundsHorizontal[i] = static_cast<float>(i) / static_cast<float>(count);
		}
	}
	
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(IScalable *first, IScalable *second, float bound, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray({first, second}), boundsHorizontal({0.f, bound, 1.f}) {}
	
	void LayerWithBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for (unsigned x = 0; x < objects.size(); ++x) {
			objectSize.x = size.x * (boundsHorizontal[x + 1] - boundsHorizontal[x]);
			objects[x]->resize(objectSize, position + coordinate);
			coordinate.x += objectSize.x;
		}
	}
	
	bool LayerWithBorderHorizontal::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position.x = position.x / size.x;
		
		unsigned object{1};
		while(position.x > boundsHorizontal[object]) ++object;
		return objects[object - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithBorderHorizontal::getMinSize() {
		sf::Vector2f minSize {0, 0};
		std::vector<sf::Vector2f> objectMinSizes(objects.size());
		for(int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSizes[i] = objects[i]->getMinSize();
		}
		
		sf::Vector2f objectMinSize;
		for (int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSize = {objectMinSizes[i].x / (boundsHorizontal[i + 1] - boundsHorizontal[i]), objectMinSizes[i].y};
			minSize = max(objectMinSize, minSize);
		}
		
		return max(minSize, this->minimumSize);
	}
	
	sf::Vector2f LayerWithBorderHorizontal::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<sf::Vector2f> objectNormalSizes(objects.size());
		for(int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSizes[i] = objects[i]->getNormalSize();
		}
		
		sf::Vector2f objectNormalSize;
		for (int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSize = {objectNormalSizes[i].x / (boundsHorizontal[i + 1] - boundsHorizontal[i]), objectNormalSizes[i].y};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	LayerWithBorderHorizontal *LayerWithBorderHorizontal::copy() {
		std::vector<IScalable *> newObjects(objects.size());
		for(int i = 0; i < newObjects.size(); ++i) {
			newObjects[i] = objects[i]->copy();
		}
		std::vector<float> newBounds(boundsHorizontal.size() - 2);
		for(int i = 0; i < newBounds.size(); ++i) {
			newBounds[i] = boundsHorizontal[i + 1];
		}
		LayerWithBorderHorizontal* layerWithBorderHorizontal{new LayerWithBorderHorizontal{newObjects, newBounds, minimumSize}};
		Layer::copy(layerWithBorderHorizontal);
		return layerWithBorderHorizontal;
	}
	
	void LayerWithBorderHorizontal::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto &object: objects) {
            object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
}