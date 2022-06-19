#include "layerWithBorderVertical.h"
#include "../../../../interaction/interactionManager/interactionManager.h"
#include <vector>

namespace ui {
	void LayerWithBorderVertical::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) {
		for (auto& object : objects) {
			initObject(object, window, interactionStack, interactionManager, parent, overlayStack);
		}
	}
	
	LayerWithBorderVertical::LayerWithBorderVertical(std::vector<IFlat *> objects, std::vector<float> boundsVertical, sf::Vector2f minSize) :
		ILayer(minSize), objects(std::move(objects)), boundsVertical(std::move(boundsVertical))  {
		this->boundsVertical.insert(this->boundsVertical.begin(), 0.0f);
		this->boundsVertical.push_back(1.0f);
	}
	
	LayerWithBorderVertical::LayerWithBorderVertical(std::vector<IFlat *> objects, sf::Vector2f minSize) :
		ILayer(minSize), objects(std::move(objects)), boundsVertical(this->objects.size() + 1, 1.0f) {
		int count = this->objects.size();
		for(int i = 0; i < count; ++i) {
			boundsVertical[i] = static_cast<float>(i) / static_cast<float>(count);
		}
	}
	
	LayerWithBorderVertical::~LayerWithBorderVertical() {
		for (auto& y : objects) {
			delete y;
		}
	}
	
	void LayerWithBorderVertical::draw() {
		for (auto& y : objects) {
			y->draw();
		}
	}
	
	void LayerWithBorderVertical::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for (unsigned y = 0; y < objects.size(); ++y) {
			objectSize.y = size.y * (boundsVertical[y + 1] - boundsVertical[y]);
			objects[y]->resize(objectSize, position + coordinate);
			coordinate.y += objectSize.y;
		}
	}
	
	bool LayerWithBorderVertical::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position.y = position.y / size.y;
		
		unsigned object{1};
		while(position.y > boundsVertical[object]) ++object;
		return objects[object - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithBorderVertical::getMinSize() {
		sf::Vector2f minimumSize {0, 0};
		std::vector<sf::Vector2f> sizes(objects.size());
		for(int i = 0; i < sizes.size(); ++i) {
			sizes[i] = objects[i]->getMinSize();
		}
		for (auto& size : sizes) {
			minimumSize.y += size.y;
		}
		for (auto& size : sizes) {
			if(minimumSize.x < size.x) {
				minimumSize.x = size.x;
			}
		}
		return {std::max(minimumSize.x, this->minimumSize.x), std::max(minimumSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f LayerWithBorderVertical::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<sf::Vector2f> sizes(objects.size());
		for(int i = 0; i < sizes.size(); ++i) {
			sizes[i] = objects[i]->getNormalSize();
		}
		for (auto& size : sizes) {
			normalSize.y += size.y;
		}
		for (auto& size : sizes) {
			if(normalSize.x < size.x) {
				normalSize.x = size.x;
			}
		}
		return normalSize;
	}
	
	void LayerWithBorderVertical::update() {
		for(IFlat* object : objects) {
			object->update();
		}
	}
	
	LayerWithBorderVertical *LayerWithBorderVertical::copy() {
		std::vector<IFlat *> newObjects(objects.size());
		for(int i = 0; i < newObjects.size(); ++i) {
			newObjects[i] = objects[i]->copy();
		}
		std::vector<float> newBounds(boundsVertical.size() - 2);
		for(int i = 0; i < newBounds.size(); ++i) {
			newBounds[i] = boundsVertical[i + 1];
		}
		LayerWithBorderVertical* layerWithBorderVertical{new LayerWithBorderVertical{newObjects, newBounds, minimumSize}};
		ILayer::copy(layerWithBorderVertical);
		return layerWithBorderVertical;
	}
}
