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
		event_handler_(&init_info.event_handler),
		slider_(&init_info.additional),
		sensitivity_(make.sensitivity),
		horizontal_(make.horizontal),
		relativity_(make.relativity == Relativity::RelationSlider) {
	}
	
	auto SliderWheelAction::update(int value) -> void {
		if(value != 0) {
			auto move{sensitivity_};
			auto reverse{(event_handler_->get_key(Key::LShift) || event_handler_->get_key(Key::RShift)) != horizontal_};
			if(relativity_) {
				auto slider_size{slider_->get_slider_size()};
				auto area_size{slider_->get_area_size()};
				move = {slider_size.x / area_size.x * move.x, slider_size.y / area_size.y * move.y};
			}
			move *= -static_cast<float>(value);
			(reverse ? move.y : move.x) = 0;
			slider_->set_value(slider_->get_value() + move);
		}
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
