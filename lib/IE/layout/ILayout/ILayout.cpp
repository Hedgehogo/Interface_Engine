#include "ILayout.hpp"

namespace ie {
	LayoutData::LayoutData() : position(), size() {
	}
	
	LayoutData::LayoutData(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {
	}
	
	void LayoutData::set_position(sf::Vector2f position) {
		this->position = position;
	}
	
	void LayoutData::move(sf::Vector2f position) {
		this->position += position;
	}
	
	void LayoutData::set_size(sf::Vector2f size) {
		this->size = size;
	}
	
	void LayoutData::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
	}
}