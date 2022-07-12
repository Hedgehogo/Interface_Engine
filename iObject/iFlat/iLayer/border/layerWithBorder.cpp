#include "layerWithBorder.h"
#include <vector>

namespace ui {
	void LayerWithBorder::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		for (auto& line : objects) {
			for (auto& object : line) {
				initObject(object, renderTarget, interactionStack, interactionManager, panelManager);
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
	
	LayerWithBorder::LayerWithBorder(std::vector<std::vector<IFlat *>> objects, sf::Vector2f minSize) :
		ILayer(minSize), objects(std::move(objects)), boundsHorizontal(this->objects.size() + 1, 1.0f), boundsVertical(this->objects[0].size() + 1, 1.0f) {
		sf::Vector2u count = {static_cast<unsigned>(this->objects.size()), static_cast<unsigned>(this->objects[0].size())};
		for(unsigned x = 0; x < count.x; ++x) {
			boundsHorizontal[x] = static_cast<float>(x) / static_cast<float>(count.x);
		}
		for(unsigned y = 0; y < count.y; ++y) {
			boundsVertical[y] = static_cast<float>(y) / static_cast<float>(count.y);
		}
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
		ILayer::resize(size, position);
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
		sf::Vector2f minSize {0, 0};
		std::vector<std::vector<sf::Vector2f>> objectMinSizes(objects.size());
		for(int x = 0; x < objectMinSizes.size(); ++x) {
			for(int y = 0; y < objectMinSizes[x].size(); ++y) {
				objectMinSizes[x][y] = objects[x][y]->getMinSize();
			}
		}
		
		sf::Vector2f lineMinSize{0, 0};
		sf::Vector2f objectMinSize{0, 0};
		for (auto & line : objectMinSizes) {
			lineMinSize.y = 0;
			for (int y = 0; y < line.size(); ++y) {
				objectMinSize.y = line[y].y / (boundsVertical[y + 1] - boundsVertical[y]);
				lineMinSize.y = std::max(objectMinSize.y, lineMinSize.y);
			}
			minSize.y = std::max(lineMinSize.y, minSize.y);
		}
		
		for (int y = 0; y < objectMinSizes[0].size(); ++y) {
			lineMinSize.x = 0;
			for (int x = 0; x < objectMinSizes.size(); ++x) {
				objectMinSize.x = objectMinSizes[x][y].x / (boundsHorizontal[x + 1] - boundsHorizontal[x]);
				lineMinSize.x = std::max(objectMinSize.x, lineMinSize.x);
			}
			minSize.x = std::max(lineMinSize.x, minSize.x);
		}
		
		return {std::max(minSize.x, this->minimumSize.x), std::max(minSize.y, this->minimumSize.y)};
	}
	
	sf::Vector2f LayerWithBorder::getNormalSize() {
		sf::Vector2f normalSize {0, 0};
		std::vector<std::vector<sf::Vector2f>> objectNormalSizes(objects.size());
		for(int x = 0; x < objectNormalSizes.size(); ++x) {
			for(int y = 0; y < objectNormalSizes[x].size(); ++y) {
				objectNormalSizes[x][y] = objects[x][y]->getNormalSize();
			}
		}
		
		sf::Vector2f lineNormalSize{0, 0};
		sf::Vector2f objectNormalSize{0, 0};
		for (auto & line : objectNormalSizes) {
			lineNormalSize.y = 0;
			for (int y = 0; y < line.size(); ++y) {
				objectNormalSize.y = line[y].y / (boundsVertical[y + 1] - boundsVertical[y]);
				lineNormalSize.y = std::max(objectNormalSize.y, lineNormalSize.y);
			}
			normalSize.y = std::max(lineNormalSize.y, normalSize.y);
		}
		
		for (int y = 0; y < objectNormalSizes[0].size(); ++y) {
			lineNormalSize.x = 0;
			for (int x = 0; x < objectNormalSizes.size(); ++x) {
				objectNormalSize.x = objectNormalSizes[x][y].x / (boundsHorizontal[x + 1] - boundsHorizontal[x]);
				lineNormalSize.x = std::max(objectNormalSize.x, lineNormalSize.x);
			}
			normalSize.x = std::max(lineNormalSize.x, normalSize.x);
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
	
	void LayerWithBorder::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		for(auto &line: objects) {
			for(auto &object: line) {
                object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
			}
		}
	}
}