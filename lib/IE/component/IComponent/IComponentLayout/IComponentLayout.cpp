#include "IComponentLayout.hpp"

namespace ie {
	void IComponentLayout::set_position(sf::Vector2f position) {
		auto& layout{layout_get_data()};
		resize(layout.size, position);
	}
	
	void IComponentLayout::move(sf::Vector2f position) {
		auto& layout{layout_get_data()};
		resize(layout.size, layout.position + position);
	}
	
	void IComponentLayout::set_size(sf::Vector2f size) {
		auto& layout{layout_get_data()};
		resize(size, layout.position);
	}
	
	sf::Vector2f IComponentLayout::get_area_position() const {
		return layout_get_data().position;
	}
	
	sf::Vector2f IComponentLayout::get_area_size() const {
		return layout_get_data().size;
	}
	
	bool IComponentLayout::in_area(sf::Vector2f point_position) const {
		auto& layout{layout_get_data()};
		return point_position.x > layout.position.x && point_position.x < layout.position.x + layout.size.x &&
			   point_position.y > layout.position.y && point_position.y < layout.position.y + layout.size.y;
	}
}