#include "layerWithBorder.h"
#include <vector>

namespace ui {
	void LayerWithBorder::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) {
		for (auto& line : objects) {
			for (auto& object : line) {
				initObject(object, window, interactionStack, interactionManager, parent, overlayStack);
			}
		}
	}
	
	LayerWithBorder::LayerWithBorder(std::vector<std::vector<IFlat *>> objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize) :
		ILayer(minSize), objects(std::move(objects)), boundsVertical(std::move(boundsVertical)), boundsHorizontal(std::move(boundsHorizontal)) {
		this->boundsHorizontal.insert(this->boundsHorizontal.begin(), 0.0f);
		this->boundsHorizontal.push_back(1.0f);
		this->boundsVertical.insert(this->boundsVertical.begin(), 0.0f);
		this->boundsVertical.push_back(1.0f);
	}

	LayerWithBorder::~LayerWithBorder() {
		for (auto& x : objects) {
			for (auto& j : x) {
				delete j;
			}
		}
	}

	void LayerWithBorder::draw() {
		for (auto& x : objects) {
			for (auto& j : x) {
				j->draw();
			}
		}
	}

	void LayerWithBorder::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		sf::Vector2f coordinate{ 0, 0 };
		sf::Vector2f objectSize{ size };
		for (unsigned x = 0; x < objects.size(); ++x) {
			objectSize.x = size.x * (boundsHorizontal[x + 1] - boundsHorizontal[x]);
			coordinate.y = 0;
			for (unsigned y = 0; y < objects[0].size(); ++y) {
				objectSize.y = size.y * (boundsVertical[y + 1] - boundsVertical[y]);
				objects[x][y]->resize(objectSize, position + coordinate);
				coordinate.y += objectSize.y;
			}
			coordinate.x += objectSize.x;
		}
	}

	bool LayerWithBorder::updateInteractions(sf::Vector2f mousePosition) {
		sf::Vector2f position{mousePosition.x - this->position.x, mousePosition.y - this->position.y};
		if(position.x < 0.0f || position.x > size.x || position.y < 0.0f || position.y > size.y) return false;
		position = {position.x / size.x, position.y / size.y};
		
		sf::Vector2u object{1, 1};
		while(position.x > boundsHorizontal[object.x]) ++object.x;
		while(position.y > boundsVertical[object.y]) ++object.y;
		return objects[object.x - 1][object.y - 1]->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithBorder::getMinSize() {
		sf::Vector2f minimumSize {0, 0};
		std::vector<std::vector<sf::Vector2f>> sizes(objects.size());
		for(int x = 0; x < sizes.size(); ++x) {
			for(int y = 0; y < sizes[x].size(); ++y) {
				sizes[x][y] = objects[x][y]->getNormalSize();
			}
		}
		for (auto& line : sizes) {
			float verticalSize{0};
			for (auto& size : line) {
				if(verticalSize < size.x) {
					verticalSize = size.x;
				}
			}
			minimumSize.y += verticalSize;
		}
		for(int y = 0; y < sizes[0].size(); ++y) {
			float horizontalSize{0};
			for(int x = 0; x < sizes.size(); ++x) {
				if(horizontalSize < sizes[x][y].y) {
					horizontalSize = sizes[x][y].y;
				}
			}
			minimumSize.x += horizontalSize;
		}
		if(minimumSize.x < this->minimumSize.x){
			minimumSize.x = this->minimumSize.x;
		}
		if(minimumSize.y < this->minimumSize.y){
			minimumSize.y = this->minimumSize.y;
		}
		return minimumSize;
	}
	
	sf::Vector2f LayerWithBorder::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<std::vector<sf::Vector2f>> sizes(objects.size());
		for(int x = 0; x < sizes.size(); ++x) {
			for(int y = 0; y < sizes[x].size(); ++y) {
				sizes[x][y] = objects[x][y]->getNormalSize();
			}
		}
		for (auto& line : sizes) {
			float verticalSize{0};
			for (auto& size : line) {
				if(verticalSize < size.x) {
					verticalSize = size.x;
				}
			}
			normalSize.y += verticalSize;
		}
		for(int y = 0; y < sizes[0].size(); ++y) {
			float horizontalSize{0};
			for(int x = 0; x < sizes.size(); ++x) {
				if(horizontalSize < sizes[x][y].y) {
					horizontalSize = sizes[x][y].y;
				}
			}
			normalSize.x += horizontalSize;
		}
		return normalSize;
	}
	
	void LayerWithBorder::update() {
		for(std::vector<IFlat*>& line : objects) {
			for(IFlat* object : line) {
				object->update();
			}
		}
	}
	
	LayerWithBorder *LayerWithBorder::copy() {
		sf::Vector2u count(objects.size(), 0);
		if(count.x != 0) {
			count.y = objects[0].size();
		}
		std::vector<std::vector<IFlat *>> newObjects(count.x, std::vector<IFlat *>(count.y, nullptr));
		for(int x = 0; x < count.x; ++x) {
			for(int y = 0; y < count.y; ++y) {
				newObjects[x][y] = objects[x][y]->copy();
			}
		}
		std::vector<float> newBoundsHorizontal(boundsHorizontal.size() - 2);
		for(int i = 0; i < newBoundsHorizontal.size(); ++i) {
			newBoundsHorizontal[i] = boundsHorizontal[i + 1];
		}
		std::vector<float> newBoundsVertical(boundsVertical.size() - 2);
		for(int i = 0; i < newBoundsVertical.size(); ++i) {
			newBoundsVertical[i] = boundsVertical[i + 1];
		}
		LayerWithBorder* layerWithBorder{new LayerWithBorder{newObjects, newBoundsHorizontal, newBoundsVertical, minimumSize}};
		ILayer::copy(layerWithBorder);
		return layerWithBorder;
	}
}