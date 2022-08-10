#include "layer.hpp"

ui::Layer::Layer(sf::Vector2f minSize, sf::Vector2f size) :
	Layout(size), minimumSize(minSize) {}

void ui::Layer::resize(sf::Vector2f size, sf::Vector2f position) {
	Layout::resize(size, position);
}

void ui::Layer::copy(ui::Layer *layer) {
	Layout::copy(layer);
}
