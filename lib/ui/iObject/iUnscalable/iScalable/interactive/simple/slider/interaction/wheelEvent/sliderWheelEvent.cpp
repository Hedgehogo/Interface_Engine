#include "sliderWheelEvent.hpp"
#include "../../baseSlider.hpp"

ui::SliderWheelEvent::Relativity ui::SliderWheelEvent::createRelativityFromYaml(const YAML::Node &node) {
	if(createBoolFromYaml(node, "relationArea", "relationSlider")) {
		return ui::SliderWheelEvent::Relativity::relationArea;
	} else {
		return ui::SliderWheelEvent::Relativity::relationSlider;
	}
}

ui::SliderWheelEvent::SliderWheelEvent(BaseSlider &slider, bool horizontal, Relativity relativity, sf::Vector2f sensitivity) :
	slider(&slider), sensitivity(sensitivity), horizontal(horizontal), relativity(relativity == Relativity::relationSlider) {}

void ui::SliderWheelEvent::startPressed(sf::Vector2i, int) {}

void ui::SliderWheelEvent::stopPressed(sf::Vector2i, int) {}

void ui::SliderWheelEvent::whilePressed(sf::Vector2i, int value) {
	sf::Vector2f move{sensitivity};
	if(relativity) {
		sf::Vector2f sliderSize{slider->getSliderSize()};
		sf::Vector2f areaSize{slider->getSliderSize()};
		move = {sliderSize.x / areaSize.x * move.x,sliderSize.y / areaSize.y * move.y};
	}
	move *= -static_cast<float>(value);
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) != horizontal) {
		move.y = 0;
	} else {
		move.x = 0;
	}
	slider->setValue(slider->getValue() + move);
}

void ui::SliderWheelEvent::whileNotPressed(sf::Vector2i, int) {}

void ui::SliderWheelEvent::setSlider(ui::BaseSlider &slider) {
	this->slider = &slider;
}

ui::SliderWheelEvent *ui::SliderWheelEvent::copy() {
	SliderWheelEvent* sliderWheelEvent{new SliderWheelEvent{*slider, horizontal, (relativity ? Relativity::relationSlider : Relativity::relationArea), sensitivity}};
	WheelEvent::copy(sliderWheelEvent);
	return sliderWheelEvent;
}
