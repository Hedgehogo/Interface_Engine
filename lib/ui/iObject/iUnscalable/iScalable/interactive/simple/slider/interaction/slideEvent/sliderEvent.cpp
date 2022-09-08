#include "sliderEvent.hpp"
#include "../../baseSlider.hpp"
#include <cmath>

ui::SliderEvent::SliderEvent(BaseSlider &slider, sf::Vector2i division) :
	slider(&slider), division(division), startMousePosition(), startValue() {}

void ui::SliderEvent::startPressed() {
	if(!slider->onSlider(mousePosition)) {
		slider->setValueByMouse(mousePosition);
	}
	startValue = slider->getValue();
	startMousePosition = mousePosition;
}

void ui::SliderEvent::stopPressed() {}

void ui::SliderEvent::whilePressed() {
	sf::Vector2i mouseOffset{mousePosition.x - startMousePosition.x, mousePosition.y - startMousePosition.y};
	slider->setValue(startValue);
	slider->moveSlider(mouseOffset);
	slider->roundValueToDivision(division);
}

void ui::SliderEvent::whileNotPressed() {}

void ui::SliderEvent::setSlider(ui::BaseSlider &slider) {
	this->slider = &slider;
}

void ui::SliderEvent::copy(ui::SliderEvent *sliderEvent) {
	sliderEvent->startMousePosition = this->startMousePosition;
	sliderEvent->startValue = this->startValue;
}

ui::SliderEvent *ui::SliderEvent::copy() {
	SliderEvent* sliderEvent{new SliderEvent{*slider, division}};
	SliderEvent::copy(sliderEvent);
	return sliderEvent;
}
