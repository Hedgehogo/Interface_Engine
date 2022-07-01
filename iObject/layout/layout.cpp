#include "layout.h"

namespace ui {
	Layout::Layout(sf::Vector2f size) : size(size), position({0, 0}) {}
	
	void Layout::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		this->size = size;
	}
	
	sf::Vector2f Layout::getPosition() {
		return position;
	}
	
	sf::Vector2f Layout::getAreaSize() {
		return size;
	}
	
	void Layout::copy(Layout *layout) {
		layout->size = this->size;
		layout->position = this->position;
	}
}