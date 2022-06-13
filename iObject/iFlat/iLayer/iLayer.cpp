#include "iLayer.h"

ui::ILayer::ILayer(sf::Vector2f minSize, sf::Vector2f size) :
	minimumSize(minSize), position(sf::Vector2f()), size(size) {}

void ui::ILayer::copy(ui::ILayer *iLayer) {
	iLayer->size = this->size;
	iLayer->position = this->position;
}
