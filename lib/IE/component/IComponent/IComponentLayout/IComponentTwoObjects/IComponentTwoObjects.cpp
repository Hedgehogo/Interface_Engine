#include "IComponentTwoObjects.hpp"

namespace ie {
	auto IComponentTwoObjects::get_min_size() const -> sf::Vector2f {
		return max(get_first_object().get_min_size(), get_second_object().get_min_size());
	}
	
	auto IComponentTwoObjects::get_normal_size() const -> sf::Vector2f {
		return max(get_first_object().get_normal_size(), get_second_object().get_normal_size());
	}
	
	auto IComponentTwoObjects::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		get_first_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		get_second_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}