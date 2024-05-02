#include "SliderAction.hpp"
#include "../BaseSlider.hpp"
#include <cmath>

namespace ie {
	SliderAction::Make::Make(sf::Vector2i division) : division(division) {
	}
	
	auto SliderAction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderAction* {
		return new SliderAction{std::move(*this), init_info};
	}
	
	SliderAction::SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		slider_(&init_info.additional), division_(make.division) {
	}
	
	auto SliderAction::get_mouse_position() -> sf::Vector2f {
		return sf::Vector2f{point_position_};
	}
	
	auto SliderAction::start_pressed() -> void {
		if(!slider_->on_slider(point_position_)) {
			slider_->set_value_by_mouse(point_position_);
		}
		start_value_ = slider_->get_value();
		start_mouse_position_ = point_position_;
	}
	
	auto SliderAction::stop_pressed() -> void {
	}
	
	auto SliderAction::while_pressed() -> void {
		auto const mouse_offset{sf::Vector2f{sf::Vector2i{
			point_position_.x - start_mouse_position_.x,
			point_position_.y - start_mouse_position_.y
		}}};
		slider_->set_value(BaseSlider::round_value_to_division(
			slider_->move_slider(start_value_, mouse_offset),
			division_
		));
	}
	
	auto SliderAction::while_not_pressed() -> void {
	}
	
	auto SliderAction::set_slider(BaseSlider& slider) -> void {
		this->slider_ = &slider;
	}
}
