#include "SliderWheelAction.hpp"
#include "../BaseSlider.hpp"

namespace ie {
	SliderWheelAction::Make::Make(bool horizontal, SliderWheelAction::Relativity relativity, sf::Vector2f sensitivity) :
		horizontal(horizontal), relativity(relativity), sensitivity(sensitivity) {
	}
	
	SliderWheelAction* SliderWheelAction::Make::make(BasicActionInitInfo<BaseSlider&> init_info) {
		return new SliderWheelAction{std::move(*this), init_info};
	}
	
	SliderWheelAction::SliderWheelAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info) :
		slider_(&init_info.additional),
		sensitivity_(make.sensitivity),
		horizontal_(make.horizontal),
		relativity_(make.relativity == Relativity::RelationSlider) {
	}
	
	SliderWheelAction::SliderWheelAction(bool horizontal, Relativity relativity, sf::Vector2f sensitivity) :
		sensitivity_(sensitivity), horizontal_(horizontal), relativity_(relativity == Relativity::RelationSlider) {
	}
	
	void SliderWheelAction::start_pressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::stop_pressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::while_pressed(sf::Vector2i, int value) {
		sf::Vector2f move{sensitivity_};
		bool reverse{(is_key_pressed(Key::LShift) || is_key_pressed(Key::RShift)) != horizontal_};
		if(relativity_) {
			sf::Vector2f slider_size{slider_->get_slider_size()};
			sf::Vector2f area_size{slider_->get_area_size()};
			move = {slider_size.x / area_size.x * move.x, slider_size.y / area_size.y * move.y};
		}
		move *= -static_cast<float>(value);
		(reverse ? move.y : move.x) = 0;
		slider_->set_value(slider_->get_value() + move);
	}
	
	void SliderWheelAction::while_not_pressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::set_slider(BaseSlider& slider) {
		this->slider_ = &slider;
	}
	
	SliderWheelAction* SliderWheelAction::copy() {
		return new SliderWheelAction{*this};
	}
	
	/*old_yaml_decode_impl
	bool Decode<SliderWheelAction::Relativity>::decode(const YAML::Node& node, SliderWheelAction::Relativity& relativity) {
		if(convert_bool(node, "relation-area", "relation-slider")) {
			relativity = SliderWheelAction::Relativity::RelationArea;
		} else {
			relativity = SliderWheelAction::Relativity::RelationSlider;
		}
		return true;

	}
	*/
}
