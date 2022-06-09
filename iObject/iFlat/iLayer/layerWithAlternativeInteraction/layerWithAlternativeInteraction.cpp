#include "layerWithAlternativeInteraction.h"
#include <algorithm>

ui::LayerWithAlternativeInteraction::LayerWithAlternativeInteraction(ui::IFlat *topObject, ui::IFlat *bottomObject, sf::Vector2f minimumSize) :
	ILayer({0, 0}), topObject(topObject), bottomObject(bottomObject){
	sf::Vector2f topMinSize {topObject->getMinSize()};
	sf::Vector2f bottomMinSize {bottomObject->getMinSize()};
	minimumSize = {std::max({topMinSize.x, bottomMinSize.x, minimumSize.x}), std::max({topMinSize.y, bottomMinSize.y, minimumSize.y})};
}

ui::LayerWithAlternativeInteraction::~LayerWithAlternativeInteraction() {
	delete topObject;
	delete bottomObject;
}

void ui::LayerWithAlternativeInteraction::draw() {
	bottomObject->draw();
	topObject->draw();
}

void ui::LayerWithAlternativeInteraction::resize(sf::Vector2f size, sf::Vector2f position) {
	this->size = size;
	this->position = position;
	topObject->resize(size, position);
	bottomObject->resize(size, position);
}

void ui::LayerWithAlternativeInteraction::update() {
	topObject->update();
	bottomObject->update();
}

bool ui::LayerWithAlternativeInteraction::updateInteractions(sf::Vector2f mousePosition) {
	if(!topObject->updateInteractions(mousePosition)) {
		if(!bottomObject->updateInteractions(mousePosition)) {
			return false;
		}
		return true;
	}
	return true;
}

sf::Vector2f ui::LayerWithAlternativeInteraction::getMinSize() {
	sf::Vector2f topMinSize {topObject->getMinSize()};
	sf::Vector2f bottomMinSize {bottomObject->getMinSize()};
	return {std::max({topMinSize.x, bottomMinSize.x, minimumSize.x}), std::max({topMinSize.y, bottomMinSize.y, minimumSize.y})};
}

sf::Vector2f ui::LayerWithAlternativeInteraction::getNormalSize() {
	sf::Vector2f topNormalSize {topObject->getNormalSize()};
	sf::Vector2f bottomNormalSize {bottomObject->getNormalSize()};
	return {std::max(topNormalSize.x, bottomNormalSize.x), std::max(topNormalSize.y, bottomNormalSize.y)};
}
