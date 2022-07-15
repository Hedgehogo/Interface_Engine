#include "layout.h"

namespace ui {
	Layout::Layout(sf::Vector2f size) : size(size), position({0, 0}) {}
	
	void Layout::setPosition(sf::Vector2f position) {
		this->position = position;
		resize(size, position);
	}
	
	void Layout::move(sf::Vector2f position) {
		this->position += position;
		resize(size, this->position);
	}
	
	void Layout::setSize(sf::Vector2f size) {
		this->size = size;
		resize(size, position);
	}
	
	sf::Vector2f Layout::getAreaPosition() { return position; }
	
	sf::Vector2f Layout::getPosition() { return position; }
	
	sf::Vector2f Layout::getAreaSize() { return size; }
	
	sf::Vector2f Layout::getSize() { return size; }
	
	bool Layout::inArea(sf::Vector2f pointPosition) {
		return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
			   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
	}
	
	bool Layout::in(sf::Vector2f pointPosition) {
		return pointPosition.x > position.x && pointPosition.x < position.x + size.x &&
			   pointPosition.y > position.y && pointPosition.y < position.y + size.y;
	}
	
	void Layout::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		this->size = size;
	}
	
	void Layout::copy(Layout *layout) {
		layout->size = this->size;
		layout->position = this->position;
	}
}