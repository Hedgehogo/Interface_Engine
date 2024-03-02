#include "SliderWheelAction.hpp"
#include "../BaseSlider.hpp"

namespace ie {
	SliderWheelAction::Make::Make(bool horizontal, SliderWheelAction::Relativity relativity, sf::Vector2f sensitivity) :
		horizontal(horizontal), relativity(relativity), sensitivity(sensitivity) {
	}
	
	auto SliderWheelAction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderWheelAction* {
		return new SliderWheelAction{std::move(*this), init_info};
	}
	
	SliderWheelAction::SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		slider_(&init_info.additional),
		sensitivity_(make.sensitivity),
		horizontal_(make.horizontal),
		relativity_(make.relativity == Relativity::RelationSlider) {
	}
	
	auto SliderWheelAction::start_pressed(sf::Vector2i, int) -> void {
	}
	
	auto SliderWheelAction::stop_pressed(sf::Vector2i, int) -> void {
	}
	
	auto SliderWheelAction::while_pressed(sf::Vector2i, int value) -> void {
		auto move{sensitivity_};
		auto reverse{(is_key_pressed(Key::LShift) || is_key_pressed(Key::RShift)) != horizontal_};
		if(relativity_) {
			sf::Vector2f slider_size{slider_->get_slider_size()};
			sf::Vector2f area_size{slider_->get_area_size()};
			move = {slider_size.x / area_size.x * move.x, slider_size.y / area_size.y * move.y};
		}
		move *= -static_cast<float>(value);
		(reverse ? move.y : move.x) = 0;
		slider_->set_value(slider_->get_value() + move);
	}
	
	auto SliderWheelAction::while_not_pressed(sf::Vector2i, int) -> void {
	}
	
	auto SliderWheelAction::set_slider(BaseSlider& slider) -> void {
		this->slider_ = &slider;
	}
}

auto ieml::Decode<char, ie::SliderWheelAction::Relativity>::decode(ieml::Node const& node) -> orl::Option<ie::SliderWheelAction::Relativity> {
	auto& str{node.get_raw().except().str};
	if(str == "relation-area") {
		return ie::SliderWheelAction::Relativity::RelationArea;
	} else if(str == "relation-slider") {
		return ie::SliderWheelAction::Relativity::RelationSlider;
	}
	return {};
}
