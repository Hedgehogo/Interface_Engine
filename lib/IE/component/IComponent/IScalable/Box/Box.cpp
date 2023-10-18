#include "Box.hpp"

namespace ie {
	Box::Box(sf::Vector2f min_size, sf::Vector2f size) :
		layout({}, size), minimum_size(min_size) {
	}
	
	LayoutData& Box::layout_get_data() {
		return layout;
	}
	
	const LayoutData& Box::layout_get_data() const {
		return layout;
	}
}