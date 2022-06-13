#include "sliderWheelEvent.h"
#include "../../baseSlider.h"

ui::SliderWheelEvent::SliderWheelEvent(BaseSlider &slider, bool horizontal, Sensitivity relativity, sf::Vector2f sensitivity) :
	slider(&slider), sensitivity(sensitivity), horizontal(horizontal), relativity(relativity == Sensitivity::relationSlider) {}

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

void ui::SliderWheelEvent::notPressed(sf::Vector2i, int) {}

void ui::SliderWheelEvent::setSlider(ui::BaseSlider &slider) {
	this->slider = &slider;
}

ui::SliderWheelEvent *ui::SliderWheelEvent::copy() {
	SliderWheelEvent* sliderWheelEvent{new SliderWheelEvent{*slider, horizontal, (relativity ? Sensitivity::relationSlider : Sensitivity::relationArea), sensitivity}};
	WheelEvent::copy(sliderWheelEvent);
	return sliderWheelEvent;
}
