#include "IComponentTwoObjects.hpp"

namespace ie {
	sf::Vector2f IComponentTwoObjects::get_min_size() const {
		return max(get_first_object().get_min_size(), get_second_object().get_min_size());
	}
	
	sf::Vector2f IComponentTwoObjects::get_normal_size() const {
		return max(get_first_object().get_normal_size(), get_second_object().get_normal_size());
	}
	
	void IComponentTwoObjects::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		get_first_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		get_second_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}