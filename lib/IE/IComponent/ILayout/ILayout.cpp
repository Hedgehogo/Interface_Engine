#include "ILayout.hpp"

namespace ui {
	LayoutData::LayoutData() : position(), size() {
	}
	
	LayoutData::LayoutData(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {
	}
	
	void LayoutData::setPosition(sf::Vector2f position) {
		this->position = position;
	}
	
	void LayoutData::move(sf::Vector2f position) {
		this->position += position;
	}
	
	void LayoutData::setSize(sf::Vector2f size) {
		this->size = size;
	}
	
	void LayoutData::resize(sf::Vector2f size, sf::Vector2f position) {
		this->size = size;
		this->position = position;
	}
	
	void ILayout::setPosition(sf::Vector2f position) {
		auto& layout{layoutGetData()};
		resize(layout.size, position);
	}
	
	void ILayout::move(sf::Vector2f position) {
		auto& layout{layoutGetData()};
		resize(layout.size, layout.position + position);
	}
	
	void ILayout::setSize(sf::Vector2f size) {
		auto& layout{layoutGetData()};
		resize(size, layout.position);
	}
	
	sf::Vector2f ILayout::getAreaPosition() const {
		return layoutGetData().position;
	}
	
	sf::Vector2f ILayout::getAreaSize() const {
		return layoutGetData().size;
	}
	
	bool ILayout::inArea(sf::Vector2f pointPosition) {
		auto& layout{layoutGetData()};
		return pointPosition.x > layout.position.x && pointPosition.x < layout.position.x + layout.size.x &&
			   pointPosition.y > layout.position.y && pointPosition.y < layout.position.y + layout.size.y;
	}
}