#include "Box.hpp"

namespace ui {
	Box::Box(sf::Vector2f minSize, sf::Vector2f size) :
		layout({}, size), minimumSize(minSize) {
	}
	
	LayoutData& Box::layoutGetData() {
		return layout;
	}
	
	const LayoutData& Box::layoutGetData() const {
		return layout;
	}
}