#include "BaseSlider.hpp"
#include <cmath>

namespace ie {
	BaseSlider::BaseSlider(
		BoxPtr<IUninteractive::Make>&& slider,
		BoxPtr<IUninteractive::Make>&& background,
		BoxPtr<SliderInteraction::Make>&& interaction,
		const PSRVec2f& value,
		InitInfo init_info
	) :
		interactive(std::move(interaction), init_info, *this),
		background(background->make(init_info)),
		slider(slider->make(init_info)),
		value(value) {
		value->add_setter([&](sf::Vector2f new_value) {
			resize_slider(new_value);
		});
		init_info.update_manager.add(*this);
		set_range_bounds(value, {0, 0}, {1, 1});
	}
	
	BaseSlider::BaseSlider(
		BoxPtr<IUninteractive>&& slider,
		BoxPtr<IUninteractive>&& background,
		BoxPtr<SliderInteraction>&& interaction,
		const PSRVec2f& value
	) :
		interactive(std::move(interaction)),
		background(std::move(background)),
		slider(std::move(slider)),
		value(value) {
		value->add_setter([this](sf::Vector2f new_value) {
			resize_slider(new_value);
		});
		set_range_bounds(value, {0, 0}, {1, 1});
	}
	
	BaseSlider::BaseSlider(const BaseSlider& other) :
		interactive(other.interactive),
		background(other.background),
		slider(other.slider),
		value(other.value) {
		dynamic_cast<SliderInteraction&>(*interactive.interaction).set_slider(*this);
		value->add_setter([this](sf::Vector2f new_value) {
			resize_slider(new_value);
		});
	}
	
	void BaseSlider::init(InitInfo init_info) {
		init_info.update_manager.add(*this);
		interactive.init(init_info, *this);
		background->init(init_info);
		slider->init(init_info);
	}
	
	void BaseSlider::resize_slider(sf::Vector2f new_value) {
		this->slider->resize(slider_size, position + sf::Vector2f(move_zone_size.x * new_value.x, move_zone_size.y * new_value.y));
	}
	
	sf::Vector2f BaseSlider::get_slider_size() {
		return slider_size;
	}
	
	sf::Vector2f BaseSlider::get_value() {
		return value->get_value();
	}
	
	void BaseSlider::set_value(sf::Vector2f value) {
		this->value->set_value(value);
	}
	
	PSRVec2f BaseSlider::get_value_ptr() {
		return value;
	}
	
	void BaseSlider::set_value_by_mouse(sf::Vector2i mouse_position) {
		sf::Vector2f mouse_offset{static_cast<sf::Vector2f>(mouse_position) - position - slider_size / 2.0f};
		value->set_value({(move_zone_size.x != 0 ? mouse_offset.x / move_zone_size.x : 0), (move_zone_size.y != 0 ? mouse_offset.y / move_zone_size.y : 0)});
	}
	
	sf::Vector2f BaseSlider::round_value_to_division(sf::Vector2f value, sf::Vector2i division) {
		sf::Vector2f divisions{division};
		if(division.x != 0) {
			value.x = std::round(value.x * divisions.x) / divisions.x;
		}
		if(division.y != 0) {
			value.y = std::round(value.y * divisions.y) / divisions.y;
		}
		return value;
	}
	
	sf::Vector2f BaseSlider::move_slider(sf::Vector2f value, sf::Vector2f offset) const {
		if(move_zone_size.x != 0) {
			value.x += offset.x / move_zone_size.x;
		}
		if(move_zone_size.y != 0) {
			value.y += offset.y / move_zone_size.y;
		}
		return value;
	}
	
	bool BaseSlider::on_slider(sf::Vector2i mouse_position) {
		sf::Vector2f mouse{static_cast<sf::Vector2f>(mouse_position)};
		sf::Vector2f slider_position{position.x + value->get_x() * move_zone_size.x, position.y + value->get_y() * move_zone_size.y};
		return
			mouse.x > slider_position.x && mouse.x < slider_position.x + slider_size.x &&
			mouse.y > slider_position.y && mouse.y < slider_position.y + slider_size.y;
	}
	
	sf::Vector2f BaseSlider::get_area_position() const {
		return position;
	}
	
	sf::Vector2f BaseSlider::get_area_size() const {
		return slider_size + move_zone_size;
	}
	
	sf::Vector2f BaseSlider::get_min_size() const {
		return background->get_min_size();
	}
	
	sf::Vector2f BaseSlider::get_normal_size() const {
		return background->get_normal_size();
	}
	
	void BaseSlider::update() {
		interactive.update();
	}
	
	bool BaseSlider::update_interactions(sf::Vector2f) {
		interactive.update_interactions();
		return true;
	}
	
	void BaseSlider::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		slider->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}
