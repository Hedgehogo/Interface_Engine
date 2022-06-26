#include "iLayer.h"

ui::ILayer::ILayer(sf::Vector2f minSize, sf::Vector2f size) :
	Layout(size), minimumSize(minSize) {}

void ui::ILayer::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
}

void ui::ILayer::copy(ui::ILayer *iLayer) {
	Layout::copy(iLayer);
}
