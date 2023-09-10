#include "IComponentLayout.hpp"

namespace ie {
	void IComponentLayout::setPosition(sf::Vector2f position) {
		auto& layout{layoutGetData()};
		resize(layout.size, position);
	}
	
	void IComponentLayout::move(sf::Vector2f position) {
		auto& layout{layoutGetData()};
		resize(layout.size, layout.position + position);
	}
	
	void IComponentLayout::setSize(sf::Vector2f size) {
		auto& layout{layoutGetData()};
		resize(size, layout.position);
	}
	
	sf::Vector2f IComponentLayout::getAreaPosition() const {
		return layoutGetData().position;
	}
	
	sf::Vector2f IComponentLayout::getAreaSize() const {
		return layoutGetData().size;
	}
	
	bool IComponentLayout::inArea(sf::Vector2f pointPosition) {
		auto& layout{layoutGetData()};
		return pointPosition.x > layout.position.x && pointPosition.x < layout.position.x + layout.size.x &&
			   pointPosition.y > layout.position.y && pointPosition.y < layout.position.y + layout.size.y;
	}
}