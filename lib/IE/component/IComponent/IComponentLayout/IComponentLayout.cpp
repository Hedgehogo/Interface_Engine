#include "IComponentLayout.hpp"

namespace ie {
	auto IComponentLayout::set_position(sf::Vector2f position) -> void {
		auto& layout{layout_get_data()};
		resize(layout.size, position);
	}
	
	auto IComponentLayout::move(sf::Vector2f offset) -> void {
		auto& layout{layout_get_data()};
		resize(layout.size, layout.position + offset);
	}
	
	auto IComponentLayout::set_size(sf::Vector2f size) -> void {
		auto& layout{layout_get_data()};
		resize(size, layout.position);
	}
	
	auto IComponentLayout::get_area_position() const -> sf::Vector2f {
		return layout_get_data().position;
	}
	
	auto IComponentLayout::get_area_size() const -> sf::Vector2f {
		return layout_get_data().size;
	}
	
	auto IComponentLayout::in_area(sf::Vector2f point_position) const -> bool {
		auto& layout{layout_get_data()};
		return point_position.x > layout.position.x && point_position.x < layout.position.x + layout.size.x &&
			   point_position.y > layout.position.y && point_position.y < layout.position.y + layout.size.y;
	}
}