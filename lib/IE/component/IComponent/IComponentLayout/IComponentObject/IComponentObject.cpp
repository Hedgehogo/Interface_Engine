#include "IComponentObject.hpp"
#include "../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	auto IComponentObject::set_position(sf::Vector2f position) -> void {
		IComponentLayout::set_position(position);
	}
	
	auto IComponentObject::move(sf::Vector2f position) -> void {
		IComponentLayout::move(position);
	}
	
	auto IComponentObject::set_size(sf::Vector2f size) -> void {
		IComponentLayout::set_size(size);
	}
	
	auto IComponentObject::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_get_data().resize(size, position);
		get_object().resize(size, position);
	}
	
	auto IComponentObject::update_interactions(Event event) -> bool {
		return get_object().update_interactions(event);
	}
	
	auto IComponentObject::get_min_size() const -> sf::Vector2f {
		return get_object().get_min_size();
	}
	
	auto IComponentObject::get_normal_size() const -> sf::Vector2f {
		return get_object().get_normal_size();
	}
	
	auto IComponentObject::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		get_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}