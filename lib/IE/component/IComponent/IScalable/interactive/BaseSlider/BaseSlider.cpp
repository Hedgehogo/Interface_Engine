#include "BaseSlider.hpp"
#include <cmath>

namespace ie {
	BaseSlider::BaseSlider(
		BoxPtr<INonInteractive::Make>&& slider,
		BoxPtr<INonInteractive::Make>&& background,
		SliderTrigger::Make&& trigger,
		MakeDyn<ISMRVec2F>&& value,
		InitInfo init_info
	) :
		trigger_(std::move(trigger), {init_info, *this}),
		background_(background->make(init_info)),
		slider_(slider->make(init_info)),
		value_(
			DynBuffer::get(std::move(value), SInitInfo{init_info}),
			[this](sf::Vector2f new_value) {
				this->resize_slider(new_value);
			}
		) {
		init_info.update_manager.add(*this);
		value_.get().get_x().set_bounds(0, 1);
		value_.get().get_y().set_bounds(0, 1);
	}
	
	auto BaseSlider::resize_slider(sf::Vector2f new_value) -> void {
		this->slider_->resize(slider_size_, position_ + sf::Vector2f{move_zone_size_.x * new_value.x, move_zone_size_.y * new_value.y});
	}
	
	auto BaseSlider::get_slider_size() -> sf::Vector2f {
		return slider_size_;
	}
	
	auto BaseSlider::get_value() -> sf::Vector2f {
		return value_.get().get();
	}
	
	auto BaseSlider::set_value(sf::Vector2f value) -> void {
		this->value_.get().set(value);
	}
	
	auto BaseSlider::get_value_ptr() -> ISMRVec2F& {
		return value_.get();
	}
	
	auto BaseSlider::set_value_by_mouse(sf::Vector2i mouse_position) -> void {
		auto mouse_offset{sf::Vector2f{mouse_position} - position_ - slider_size_ / 2.0f};
		value_.get().set(
			{
				(move_zone_size_.x != 0 ? mouse_offset.x / move_zone_size_.x : 0),
				(move_zone_size_.y != 0 ? mouse_offset.y / move_zone_size_.y : 0)
			}
		);
	}
	
	auto BaseSlider::round_value_to_division(sf::Vector2f value, sf::Vector2i division) -> sf::Vector2f {
		auto divisions{sf::Vector2f{division}};
		if(division.x != 0) {
			value.x = std::round(value.x * divisions.x) / divisions.x;
		}
		if(division.y != 0) {
			value.y = std::round(value.y * divisions.y) / divisions.y;
		}
		return value;
	}
	
	auto BaseSlider::move_slider(sf::Vector2f value, sf::Vector2f offset) const -> sf::Vector2f {
		if(move_zone_size_.x != 0) {
			value.x += offset.x / move_zone_size_.x;
		}
		if(move_zone_size_.y != 0) {
			value.y += offset.y / move_zone_size_.y;
		}
		return value;
	}
	
	auto BaseSlider::on_slider(sf::Vector2i mouse_position) -> bool {
		auto mouse{sf::Vector2f{mouse_position}};
		auto value{value_.get().get()};
		auto slider_position{sf::Vector2f{position_.x + value.x * move_zone_size_.x, position_.y + value.y * move_zone_size_.y}};
		return
			mouse.x > slider_position.x && mouse.x < slider_position.x + slider_size_.x &&
			mouse.y > slider_position.y && mouse.y < slider_position.y + slider_size_.y;
	}
	
	auto BaseSlider::get_area_position() const -> sf::Vector2f {
		return position_;
	}
	
	auto BaseSlider::get_area_size() const -> sf::Vector2f {
		return slider_size_ + move_zone_size_;
	}
	
	auto BaseSlider::get_min_size() const -> sf::Vector2f {
		return background_->get_min_size();
	}
	
	auto BaseSlider::get_normal_size() const -> sf::Vector2f {
		return background_->get_normal_size();
	}
	
	auto BaseSlider::update() -> void {
		trigger_.update();
	}
	
	auto BaseSlider::handle_event(Event event) -> bool {
		return trigger_.handle_event(event);
	}
	
	auto BaseSlider::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		slider_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}
