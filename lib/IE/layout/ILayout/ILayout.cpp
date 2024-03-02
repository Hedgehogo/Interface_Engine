#include "ILayout.hpp"

namespace ie {
	LayoutData::LayoutData() : position(), size() {
	}
	
	LayoutData::LayoutData(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {
	}
	
	auto LayoutData::set_position(sf::Vector2f position) -> void {
		this->position = position;
	}
	
	auto LayoutData::move(sf::Vector2f position) -> void {
		this->position += position;
	}
	
	auto LayoutData::set_size(sf::Vector2f size) -> void {
		this->size = size;
	}
	
	auto LayoutData::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		this->size = size;
		this->position = position;
	}
}