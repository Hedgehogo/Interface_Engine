#include "box.hpp"

namespace ui {
	Box::Box(sf::Vector2f minSize, sf::Vector2f size) :
		layout({}, size), minimumSize(minSize) {
	}
	
	void Box::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayout::resize(size, position);
	}
	
	LayoutData& Box::getLayoutData() {
		return layout;
	}
	
	const LayoutData& Box::getLayoutData() const {
		return layout;
	}
}