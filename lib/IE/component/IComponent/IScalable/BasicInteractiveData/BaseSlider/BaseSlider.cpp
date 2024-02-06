#include "BaseSlider.hpp"
#include <cmath>

namespace ie {
	BaseSlider::BaseSlider(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		BoxPtr<SliderInteraction::Make>&& interaction,
		MakeDyn<ISMRVec2F>&& value,
		InitInfo init_info
	) :
		interactive_(std::move(interaction), init_info, *this),
		background_(background->make(init_info)),
		slider_(slider->make(init_info)),
		value_(
			init_info.dyn_buffer.get(std::move(value)),
			[this](sf::Vector2f new_value) {
				this->resize_slider(new_value);
			}
		) {
		init_info.update_manager.add(*this);
		value_.get().get_x().set_bounds(0, 1);
		value_.get().get_y().set_bounds(0, 1);
	}
	
	void BaseSlider::resize_slider(sf::Vector2f new_value) {
		this->slider_->resize(slider_size_, position_ + sf::Vector2f(move_zone_size_.x * new_value.x, move_zone_size_.y * new_value.y));
	}
	
	sf::Vector2f BaseSlider::get_slider_size() {
		return slider_size_;
	}
	
	sf::Vector2f BaseSlider::get_value() {
		return value_.get().get();
	}
	
	void BaseSlider::set_value(sf::Vector2f value) {
		this->value_.get().set(value);
	}
	
	ISMRVec2F& BaseSlider::get_value_ptr() {
		return value_.get();
	}
	
	void BaseSlider::set_value_by_mouse(sf::Vector2i mouse_position) {
		sf::Vector2f mouse_offset{static_cast<sf::Vector2f>(mouse_position) - position_ - slider_size_ / 2.0f};
		value_.get().set(
			{
				(move_zone_size_.x != 0 ? mouse_offset.x / move_zone_size_.x : 0),
				(move_zone_size_.y != 0 ? mouse_offset.y / move_zone_size_.y : 0)
			}
		);
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
		if(move_zone_size_.x != 0) {
			value.x += offset.x / move_zone_size_.x;
		}
		if(move_zone_size_.y != 0) {
			value.y += offset.y / move_zone_size_.y;
		}
		return value;
	}
	
	bool BaseSlider::on_slider(sf::Vector2i mouse_position) {
		sf::Vector2f mouse{static_cast<sf::Vector2f>(mouse_position)};
		sf::Vector2f value{value_.get().get()};
		sf::Vector2f slider_position{position_.x + value.x * move_zone_size_.x, position_.y + value.y * move_zone_size_.y};
		return
			mouse.x > slider_position.x && mouse.x < slider_position.x + slider_size_.x &&
			mouse.y > slider_position.y && mouse.y < slider_position.y + slider_size_.y;
	}
	
	sf::Vector2f BaseSlider::get_area_position() const {
		return position_;
	}
	
	sf::Vector2f BaseSlider::get_area_size() const {
		return slider_size_ + move_zone_size_;
	}
	
	sf::Vector2f BaseSlider::get_min_size() const {
		return background_->get_min_size();
	}
	
	sf::Vector2f BaseSlider::get_normal_size() const {
		return background_->get_normal_size();
	}
	
	void BaseSlider::update() {
		interactive_.update();
	}
	
	bool BaseSlider::update_interactions(sf::Vector2f) {
		interactive_.update_interactions();
		return true;
	}
	
	void BaseSlider::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		slider_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}
