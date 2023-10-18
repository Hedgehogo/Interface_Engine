#include "IComponentObject.hpp"
#include "../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	void IComponentObject::set_position(sf::Vector2f position) {
		IComponentLayout::set_position(position);
	}
	
	void IComponentObject::move(sf::Vector2f position) {
		IComponentLayout::move(position);
	}
	
	void IComponentObject::set_size(sf::Vector2f size) {
		IComponentLayout::set_size(size);
	}
	
	void IComponentObject::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_get_data().resize(size, position);
		get_object().resize(size, position);
	}
	
	bool IComponentObject::update_interactions(sf::Vector2f mouse_position) {
		return get_object().update_interactions(mouse_position);
	}
	
	sf::Vector2f IComponentObject::get_min_size() const {
		return get_object().get_min_size();
	}
	
	sf::Vector2f IComponentObject::get_normal_size() const {
		return get_object().get_normal_size();
	}
	
	void IComponentObject::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		get_object().draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}