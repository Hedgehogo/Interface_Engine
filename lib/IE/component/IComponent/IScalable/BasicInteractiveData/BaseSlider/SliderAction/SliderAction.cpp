#include "SliderAction.hpp"
#include "../BaseSlider.hpp"
#include <cmath>

namespace ie {
	SliderAction::Make::Make(sf::Vector2i division) : division(division) {
	}
	
	SliderAction* SliderAction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) {
		return new SliderAction{std::move(*this), init_info};
	}
	
	SliderAction::SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		slider_(&init_info.additional), division_(make.division) {
	}
	
	SliderAction::SliderAction(sf::Vector2i division) :
		slider_(nullptr), start_mouse_position_(), start_value_(), division_(division) {
	}
	
	void SliderAction::init(BasicActionInitInfo<BaseSlider&> init_info) {
		slider_ = &init_info.additional;
	}
	
	sf::Vector2f SliderAction::get_mouse_position() {
		return sf::Vector2f{mouse_position};
	}
	
	void SliderAction::start_pressed() {
		if(!slider_->on_slider(mouse_position)) {
			slider_->set_value_by_mouse(mouse_position);
		}
		start_value_ = slider_->get_value();
		start_mouse_position_ = mouse_position;
	}
	
	void SliderAction::stop_pressed() {
	}
	
	void SliderAction::while_pressed() {
		sf::Vector2f mouse_offset{sf::Vector2i{mouse_position.x - start_mouse_position_.x, mouse_position.y - start_mouse_position_.y}};
		sf::Vector2f new_value;
		new_value = slider_->move_slider(start_value_, mouse_offset);
		new_value = BaseSlider::round_value_to_division(new_value, division_);
		slider_->set_value(new_value);
	}
	
	void SliderAction::while_not_pressed() {
	}
	
	void SliderAction::set_slider(BaseSlider& slider) {
		this->slider_ = &slider;
	}
	
	SliderAction* SliderAction::copy() {
		return new SliderAction{*this};
	}
}
