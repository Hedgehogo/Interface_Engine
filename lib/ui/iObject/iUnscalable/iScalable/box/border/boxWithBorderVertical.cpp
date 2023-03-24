#include "boxWithBorderVertical.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.hpp"
#include <vector>

namespace ui {
	BoxWithBorderVertical::BoxWithBorderVertical(std::vector<IScalable *> objects, std::vector<float> bounds, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray(std::move(objects)), bounds(std::move(bounds))  {
		this->bounds.insert(this->bounds.begin(), 0.0f);
		this->bounds.push_back(1.0f);
	}
	
	BoxWithBorderVertical::BoxWithBorderVertical(std::vector<IScalable *> objects, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray(std::move(objects)), bounds(this->objects.size() + 1, 1.0f) {
		auto count = this->objects.size();
		for(unsigned long long i = 0; i < count; ++i) {
			bounds[i] = static_cast<float>(i) / static_cast<float>(count);
		}
	}
	
	BoxWithBorderVertical::BoxWithBorderVertical(IScalable *firstObject, IScalable *secondObject, float bound, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObjectsArray({firstObject, secondObject}), bounds({0.f, bound, 1.f}) {}
	
	void BoxWithBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for(unsigned y = 0; y < objects.size(); ++y) {
			objectSize.y = size.y * (bounds[y + 1] - bounds[y]);
			objects[y]->resize(objectSize, position + coordinate);
			coordinate.y += objectSize.y;
		}
	}
	
	bool BoxWithBorderVertical::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position.y = position.y / size.y;
		
		unsigned long long i{1};
		while(position.y > bounds[i]) ++i;
		return objects[i - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxWithBorderVertical::getMinSize() {
		sf::Vector2f minSize {0, 0};
		std::vector<sf::Vector2f> objectMinSizes(objects.size());
		for(int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSizes[i] = objects[i]->getMinSize();
		}
		
		sf::Vector2f objectMinSize;
		for (int i = 0; i < objectMinSizes.size(); ++i) {
			objectMinSize = {objectMinSizes[i].x, objectMinSizes[i].y / (bounds[i + 1] - bounds[i])};
			minSize = max(objectMinSize, minSize);
		}
		
		return max(minSize, this->minimumSize);
	}
	
	sf::Vector2f BoxWithBorderVertical::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<sf::Vector2f> objectNormalSizes(objects.size());
		for(int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSizes[i] = objects[i]->getNormalSize();
		}
		
		sf::Vector2f objectNormalSize;
		for (int i = 0; i < objectNormalSizes.size(); ++i) {
			objectNormalSize = {objectNormalSizes[i].x, objectNormalSizes[i].y / (bounds[i + 1] - bounds[i])};
			normalSize = max(objectNormalSize, normalSize);
		}
		
		return normalSize;
	}
	
	BoxWithBorderVertical *BoxWithBorderVertical::copy() {
		std::vector<IScalable *> newObjects(objects.size());
		for(int i = 0; i < newObjects.size(); ++i) {
			newObjects[i] = objects[i]->copy();
		}
		std::vector<float> newBounds(bounds.size() - 2);
		for(int i = 0; i < newBounds.size(); ++i) {
			newBounds[i] = bounds[i + 1];
		}
		BoxWithBorderVertical* boxWithBorderVertical{new BoxWithBorderVertical{newObjects, newBounds, minimumSize}};
		Box::copy(boxWithBorderVertical);
		return boxWithBorderVertical;
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithBorderVertical *&boxWithBorderVertical) {
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
				
				{ boxWithBorderVertical = new BoxWithBorderVertical{objects, bounds, minSize}; return true; }
			} else {
				{ boxWithBorderVertical = new BoxWithBorderVertical{objects, minSize}; return true; }
			}
		} else {
			IScalable *firstObject;
			IScalable *secondObject;
			float bound{0.5f};
			
			node["first-object"] >> firstObject;
			node["second-object"] >> secondObject;
			if(node["bound"])
				node["bound"] >> bound;
			
			{ boxWithBorderVertical = new BoxWithBorderVertical{firstObject, secondObject, bound, minSize}; return true; }
		}
	}
	
	void BoxWithBorderVertical::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto &object: objects) {
            object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		}
	}
}
