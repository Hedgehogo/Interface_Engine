#include "IComponentObjectsArray.hpp"

namespace ie {
	void IComponentObjectsArray::set_position(sf::Vector2f position) {
		IComponentObjectsArray::move(position - layout_get_data().position);
	}
	
	void IComponentObjectsArray::move(sf::Vector2f position) {
		layout_get_data().move(position);
		for(std::size_t i = 0; i < get_array_size(); ++i) {
			get_object_at(i).move(position);
		}
	}
	
	void IComponentObjectsArray::set_size(sf::Vector2f size) {
		IComponentLayout::set_size(size);
	}
	
	sf::Vector2f IComponentObjectsArray::get_min_size() const {
		sf::Vector2f min_size{0, 0};
		for(std::size_t i = 0; i < get_array_size(); ++i) {
			min_size = max(min_size, get_object_at(i).get_min_size());
		}
		return min_size;
	}
	
	sf::Vector2f IComponentObjectsArray::get_normal_size() const {
		sf::Vector2f normal_size{0, 0};
		for(std::size_t i = 0; i < get_array_size(); ++i) {
			normal_size = max(normal_size, get_object_at(i).get_normal_size());
		}
		return normal_size;
	}
	
	void IComponentObjectsArray::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, uint hue, uint hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		for(std::size_t i = 0; i < get_array_size(); ++i) {
			get_object_at(i).draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		}
	}
}