#include "Box.hpp"

namespace ie {
	Box::Box(sf::Vector2f min_size, sf::Vector2f size) :
		layout_({}, size), minimum_size_(min_size) {
	}
	
	auto Box::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto Box::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}