#include "IComponentBackground.hpp"

namespace ie {
	void IComponentBackground::set_position(sf::Vector2f position) {
		IComponentLayout::set_position(position);
	}
	
	void IComponentBackground::move(sf::Vector2f position) {
		IComponentLayout::move(position);
	}
	
	void IComponentBackground::set_size(sf::Vector2f size) {
		IComponentLayout::set_size(size);
	}
	
	void IComponentBackground::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_get_data().resize(size, position);
		get_background().resize(size, position);
	}
	
	sf::Vector2f IComponentBackground::get_min_size() const {
		return get_background().get_min_size();
	}
	
	sf::Vector2f IComponentBackground::get_normal_size() const {
		return get_background().get_normal_size();
	}
	
	void IComponentBackground::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		get_background().draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}