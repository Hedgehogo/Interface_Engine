#include "layerWithConstBezel.h"

namespace ui {
	void LayerWithConstBezel::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		initObject(object, window, interactionStack, interactionManager, panelManager);
		initObject(bezel, window, interactionStack, interactionManager, panelManager);
	}
	
	LayerWithConstBezel::LayerWithConstBezel(IFlat *object, IDrawn *bezel, float thickness, sf::Vector2f minSize) :
		ILayer(minSize), object(object), bezel(bezel), thickness(thickness) {
		sf::Vector2f minimumSize{object->getMinSize() + sf::Vector2f(thickness * 2.0f, thickness * 2.0f)};
		if(this->minimumSize.x < minimumSize.x) {
			this->minimumSize.x = minimumSize.x;
		}
		if(this->minimumSize.y < minimumSize.y) {
			this->minimumSize.y = minimumSize.y;
		}
	}
	
	LayerWithConstBezel::~LayerWithConstBezel() {
		delete object;
		delete bezel;
	}
	
	void LayerWithConstBezel::draw() {
		bezel->draw();
		object->draw();
	}
	
	void LayerWithConstBezel::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		bezel->resize(size, position);
		object->resize(size - sf::Vector2f(thickness * 2.0f, thickness * 2.0f), position + sf::Vector2f(thickness, thickness));
	}
	
	bool LayerWithConstBezel::updateInteractions(sf::Vector2f mousePosition) {
		if((mousePosition.x >= position.x + thickness) && (mousePosition.x <= position.x + size.x - thickness) &&
			(mousePosition.y >= position.y + thickness) && (mousePosition.y <= position.y + size.y - thickness)) {
			return object->updateInteractions(mousePosition);
		}
		return bezel->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstBezel::getMinSize() {
		sf::Vector2f objectMinSize {object->getMinSize()};
		sf::Vector2f bezelMinSize {bezel->getMinSize()};
		return {std::max({objectMinSize.x + thickness * 2, bezelMinSize.x, minimumSize.x}), std::max({objectMinSize.y + thickness * 2, bezelMinSize.y, minimumSize.y})};
	}
	
	sf::Vector2f LayerWithConstBezel::getNormalSize() {
		sf::Vector2f objectNormalSize {object->getNormalSize()};
		sf::Vector2f bezelMinSize {bezel->getMinSize()};
		return {std::max(objectNormalSize.x + thickness * 2, bezelMinSize.x), std::max(objectNormalSize.y + thickness * 2, bezelMinSize.y)};
	}
	
	void LayerWithConstBezel::update() {
		object->update();
	}
	
	LayerWithConstBezel *LayerWithConstBezel::copy() {
		return new LayerWithConstBezel{object->copy(), bezel->copy(), thickness};
	}
}
