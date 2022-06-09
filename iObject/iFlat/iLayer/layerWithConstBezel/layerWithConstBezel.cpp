#include "layerWithConstBezel.h"

namespace ui {
	void LayerWithConstBezel::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) {
		initObject(object, window, interactionStack, interactionManager, parent, overlayStack);
		initObject(bezel, window, interactionStack, interactionManager, parent, overlayStack);
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
		return minimumSize;
	}
	
	sf::Vector2f LayerWithConstBezel::getNormalSize() {
		return object->getNormalSize() + sf::Vector2f(thickness * 2, thickness * 2);
	}
	
	void LayerWithConstBezel::update() {
		object->update();
	}
}
