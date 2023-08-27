#include "SliderWheelAction.hpp"
#include "../BaseSlider.hpp"

namespace ie {
	SliderWheelAction::SliderWheelAction(BaseSlider& slider, bool horizontal, Relativity relativity, sf::Vector2f sensitivity) :
		slider(&slider), sensitivity(sensitivity), horizontal(horizontal), relativity(relativity == Relativity::relationSlider) {
	}
	
	void SliderWheelAction::startPressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::stopPressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::whilePressed(sf::Vector2i, int value) {
		sf::Vector2f move{sensitivity};
		bool reverse{(isKeyPressed(Key::lShift) || isKeyPressed(Key::rShift)) != horizontal};
		if(relativity) {
			sf::Vector2f sliderSize{slider->getSliderSize()};
			sf::Vector2f areaSize{slider->getAreaSize()};
			move = {sliderSize.x / areaSize.x * move.x, sliderSize.y / areaSize.y * move.y};
		}
		move *= -static_cast<float>(value);
		(reverse ? move.y : move.x) = 0;
		slider->setValue(slider->getValue() + move);
	}
	
	void SliderWheelAction::whileNotPressed(sf::Vector2i, int) {
	}
	
	void SliderWheelAction::setSlider(BaseSlider& slider) {
		this->slider = &slider;
	}
	
	SliderWheelAction* SliderWheelAction::copy() {
		return new SliderWheelAction{*this};
	}
	
	bool Decode<SliderWheelAction::Relativity>::decode(const YAML::Node& node, SliderWheelAction::Relativity& relativity) {
		if(convertBool(node, "relation-area", "relation-slider")) {
			relativity = SliderWheelAction::Relativity::relationArea;
		} else {
			relativity = SliderWheelAction::Relativity::relationSlider;
		}
		return true;
	}
}
