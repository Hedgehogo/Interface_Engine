#include "SliderEvent.hpp"
#include "../BaseSlider.hpp"
#include <cmath>

namespace ui {
	SliderEvent::SliderEvent(BaseSlider& slider, sf::Vector2i division) :
		slider(&slider), startMousePosition(), startValue(), division(division) {
	}
	
	sf::Vector2f SliderEvent::getMousePosition() {
		return sf::Vector2f{mousePosition};
	}
	
	void SliderEvent::startPressed() {
		if(!slider->onSlider(mousePosition)) {
			slider->setValueByMouse(mousePosition);
		}
		startValue = slider->getValue();
		startMousePosition = mousePosition;
	}
	
	void SliderEvent::stopPressed() {
	}
	
	void SliderEvent::whilePressed() {
		sf::Vector2f mouseOffset{sf::Vector2i{mousePosition.x - startMousePosition.x, mousePosition.y - startMousePosition.y}};
		sf::Vector2f newValue;
		newValue = slider->moveSlider(startValue, mouseOffset);
		newValue = BaseSlider::roundValueToDivision(newValue, division);
		slider->setValue(newValue);
	}
	
	void SliderEvent::whileNotPressed() {
	}
	
	void SliderEvent::setSlider(BaseSlider& slider) {
		this->slider = &slider;
	}
	
	SliderEvent* SliderEvent::copy() {
		return new SliderEvent{*this};
	}
}
