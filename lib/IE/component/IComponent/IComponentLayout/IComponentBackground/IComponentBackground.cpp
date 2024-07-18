#include "IComponentBackground.hpp"

namespace ie {
	auto IComponentBackground::set_position(sf::Vector2f position) -> void {
		IComponentLayout::set_position(position);
	}
	
	auto IComponentBackground::move(sf::Vector2f offset) -> void {
		IComponentLayout::move(offset);
	}
	
	auto IComponentBackground::set_size(sf::Vector2f size) -> void {
		IComponentLayout::set_size(size);
	}
	
	auto IComponentBackground::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_get_data().resize(size, position);
		get_background().resize(size, position);
	}
	
	auto IComponentBackground::get_min_size() const -> sf::Vector2f {
		return get_background().get_min_size();
	}
	
	auto IComponentBackground::get_normal_size() const -> sf::Vector2f {
		return get_background().get_normal_size();
	}
	
	auto IComponentBackground::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		get_background().draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}