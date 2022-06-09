#include "layerWithBorderHorizontal.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../interaction/interactionManager/interactionManager.h"
#include <vector>

namespace ui {
	void LayerWithBorderHorizontal::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) {
		for (auto& object : objects) {
			initObject(object, window, interactionStack, interactionManager, parent, overlayStack);
		}
	}
	
	LayerWithBorderHorizontal::LayerWithBorderHorizontal(std::vector<IFlat *> objects, std::vector<float> bounds, sf::Vector2f minSize) :
		ILayer(minSize), objects(std::move(objects)), boundsHorizontal(std::move(bounds)) {
		this->boundsHorizontal.insert(this->boundsHorizontal.begin(), 0.0f);
		this->boundsHorizontal.push_back(1.0f);
	}
	
	LayerWithBorderHorizontal::~LayerWithBorderHorizontal() {
		for (auto& i : objects) {
			delete i;
		}
	}
	
	void LayerWithBorderHorizontal::draw() {
		for (auto& i : objects) {
			i->draw();
		}
	}
	
	void LayerWithBorderHorizontal::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
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
		sf::Vector2f minimumSize {0, 0};
		std::vector<sf::Vector2f> sizes(objects.size());
		for(int i = 0; i < sizes.size(); ++i) {
			sizes[i] = objects[i]->getMinSize();
		}
		for (auto& size : sizes) {
			minimumSize.x += size.x;
		}
		for (auto& size : sizes) {
			if(minimumSize.y < size.y) {
				minimumSize.y = size.y;
			}
		}
		if(minimumSize.x < this->minimumSize.x){
			minimumSize.x = this->minimumSize.x;
		}
		if(minimumSize.y < this->minimumSize.y){
			minimumSize.y = this->minimumSize.y;
		}
		return minimumSize;
	}
	
	sf::Vector2f LayerWithBorderHorizontal::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<sf::Vector2f> sizes(objects.size());
		for(int i = 0; i < sizes.size(); ++i) {
			sizes[i] = objects[i]->getNormalSize();
		}
		for (auto& size : sizes) {
			normalSize.x += size.x;
		}
		for (auto& size : sizes) {
			if(normalSize.y < size.y) {
				normalSize.y = size.y;
			}
		}
		return normalSize;
	}
	
	void LayerWithBorderHorizontal::update() {
		for(IFlat* object : objects) {
			object->update();
		}
	}
}