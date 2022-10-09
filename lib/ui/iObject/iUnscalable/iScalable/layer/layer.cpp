#include "layer.hpp"

namespace ui {
	Layer::Layer(sf::Vector2f minSize, sf::Vector2f size) :
		Layout(size), minimumSize(minSize) {
	}
	
	void Layer::resize(sf::Vector2f size, sf::Vector2f position) {
		Layout::resize(size, position);
	}
	
	void Layer::copy(Layer *layer) {
		Layout::copy(layer);
	}
}