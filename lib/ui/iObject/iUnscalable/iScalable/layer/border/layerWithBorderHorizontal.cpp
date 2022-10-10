#include "layerWithBorderHorizontal.hpp"
#include <vector>

namespace ui {
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(std::vector<IScalable *> objects, std::vector<float> bounds, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), bounds(std::move(bounds)) {
		this->bounds.insert(this->bounds.begin(), 0.0f);
		this->bounds.push_back(1.0f);
	}
	
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(std::vector<IScalable *> objects, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray(std::move(objects)), bounds(this->objects.size() + 1, 1.0f) {
		auto count = this->objects.size();
		for(unsigned long long i = 0; i < count; ++i) {
			bounds[i] = static_cast<float>(i) / static_cast<float>(count);
		}
	}
	
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(IScalable *firstObject, IScalable *secondObject, float bound, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithObjectsArray({firstObject, secondObject}), bounds({0.f, bound, 1.f}) {}
	
	void LayerWithBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for (unsigned x = 0; x < objects.size(); ++x) {
			objectSize.x = size.x * (bounds[x + 1] - bounds[x]);
			objects[x]->resize(objectSize, position + coordinate);
			coordinate.x += objectSize.x;
		}
	}
	
	bool LayerWithBorderHorizontal::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position.x = position.x / size.x;
		
		unsigned object{1};
		while(position.x > bounds[object]) ++object;
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
			objectMinSize = {objectMinSizes[i].x / (bounds[i + 1] - bounds[i]), objectMinSizes[i].y};
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
			objectNormalSize = {objectNormalSizes[i].x / (bounds[i + 1] - bounds[i]), objectNormalSizes[i].y};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	LayerWithBorderHorizontal *LayerWithBorderHorizontal::copy() {
		std::vector<IScalable *> newObjects(objects.size());
		for(int i = 0; i < newObjects.size(); ++i) {
			newObjects[i] = objects[i]->copy();
		}
		std::vector<float> newBounds(bounds.size() - 2);
		for(int i = 0; i < newBounds.size(); ++i) {
			newBounds[i] = bounds[i + 1];
		}
		LayerWithBorderHorizontal* layerWithBorderHorizontal{new LayerWithBorderHorizontal{newObjects, newBounds, minimumSize}};
		Layer::copy(layerWithBorderHorizontal);
		return layerWithBorderHorizontal;
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithBorderHorizontal *&layerWithBorderHorizontal) {
		sf::Vector2f minSize{};
		
		if(node["min-size"])
			node["min-size"] >> minSize;
		if(node["objects"]) {
			std::vector<IScalable *> objects(node["objects"].size());
			
			for(ullint i = 0; i < node["objects"].size(); ++i) {
				node["objects"][i] >> objects[i];
			}
			if(node["bounds"]) {
				std::vector<float> bounds(node["bounds"].size());
				
				for(ullint i = 0; i < node["bounds"].size(); ++i) {
					node["bounds"][i] >> bounds[i];
				}
				
				{ layerWithBorderHorizontal = new LayerWithBorderHorizontal{objects, bounds, minSize}; return true; }
			} else {
				{ layerWithBorderHorizontal = new LayerWithBorderHorizontal{objects, minSize}; return true; }
			}
		} else {
			IScalable *firstObject;
			IScalable *secondObject;
			float bound{0.5f};
			
			node["first-object"] >> firstObject;
			node["second-object"] >> secondObject;
			if(node["bound"])
				node["bound"] >> bound;
			
			{ layerWithBorderHorizontal = new LayerWithBorderHorizontal{firstObject, secondObject, bound, minSize}; return true; }
		}
	}
	
	void LayerWithBorderHorizontal::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto &object: objects) {
            object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
}