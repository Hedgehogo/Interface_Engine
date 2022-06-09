#include "layerWithInteractiveOverlay.h"

namespace ui {
	void LayerWithInteractiveOverlay::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &panelStack) {
		this->panelStack = &panelStack;
		initObject(object, window, interactionStack, interactionManager, parent, panelStack);
		initObject(panel, window, interactionStack, interactionManager, parent, panelStack);
	}
	
	LayerWithInteractiveOverlay::LayerWithInteractiveOverlay(Panel *panel, IFlat *object) :
		ILayer({0, 0}), panel(panel), object(object), panelStack(nullptr) {
	}
	
	LayerWithInteractiveOverlay::~LayerWithInteractiveOverlay() {
		delete panel;
		delete object;
	}
	
	void LayerWithInteractiveOverlay::draw() {
		object->draw();
	}
	
	void LayerWithInteractiveOverlay::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
		panel->resize(size, position);
		object->resize(size, position);
	}
	
	void LayerWithInteractiveOverlay::update() {
		object->update();
		panel->update();
	}
	
	bool LayerWithInteractiveOverlay::updateInteractions(sf::Vector2f mousePosition) {
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithInteractiveOverlay::getMinSize() {
		sf::Vector2f panelMinSize{panel->getMinSize()};
		sf::Vector2f objectMinSize{object->getMinSize()};
		return sf::Vector2f{std::max(panelMinSize.x, objectMinSize.x), std::max(panelMinSize.y, objectMinSize.y)};
	}
	
	sf::Vector2f LayerWithInteractiveOverlay::getNormalSize() {
		sf::Vector2f panelNormalSize{panel->getNormalSize()};
		sf::Vector2f objectNormalSize{object->getNormalSize()};
		return sf::Vector2f{std::max(panelNormalSize.x, objectNormalSize.x), std::max(panelNormalSize.y, objectNormalSize.y)};
	}
}