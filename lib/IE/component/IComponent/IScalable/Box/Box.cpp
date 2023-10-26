#include "Box.hpp"

namespace ie {
	Box::Box(sf::Vector2f min_size, sf::Vector2f size) :
		layout_({}, size), minimum_size_(min_size) {
	}
	
	LayoutData& Box::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& Box::layout_get_data() const {
		return layout_;
	}
}