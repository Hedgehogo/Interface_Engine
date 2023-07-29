#include "iLayout.hpp"

namespace ui {
	LayoutData::LayoutData() : position(), size() {
	}
	
	LayoutData::LayoutData(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {
	}
	
	void ILayout::setPosition(sf::Vector2f position) {
		auto& thisPosition{getLayoutPosition()};
		thisPosition = position;
		resize(getLayoutSize(), thisPosition);
	}
	
	void ILayout::move(sf::Vector2f position) {
		auto& thisPosition{getLayoutPosition()};
		thisPosition += position;
		resize(getLayoutSize(), thisPosition);
	}
	
	void ILayout::setSize(sf::Vector2f size) {
		auto& thisSize{getLayoutSize()};
		thisSize = size;
		resize(size, getLayoutPosition());
	}
	
	sf::Vector2f ILayout::getAreaPosition() const {
		return getLayoutPosition();
	}
	
	sf::Vector2f ILayout::getAreaSize() const {
		return getLayoutSize();
	}
	
	sf::Vector2f& ILayout::getLayoutPosition() {
		return getLayoutData().position;
	}
	
	sf::Vector2f& ILayout::getLayoutSize() {
		return getLayoutData().size;
	}
	
	const sf::Vector2f& ILayout::getLayoutPosition() const {
		return getLayoutData().position;
	}
	
	const sf::Vector2f& ILayout::getLayoutSize() const {
		return getLayoutData().size;
	}
	
	bool ILayout::inArea(sf::Vector2f pointPosition) {
		auto& thisPosition{getLayoutPosition()};
		auto& thisSize{getLayoutSize()};
		return pointPosition.x > thisPosition.x && pointPosition.x < thisPosition.x + thisSize.x &&
			   pointPosition.y > thisPosition.y && pointPosition.y < thisPosition.y + thisSize.y;
	}
	
	void ILayout::resize(sf::Vector2f size, sf::Vector2f position) {
		getLayoutPosition() = position;
		getLayoutSize() = size;
	}
}