#include "SliderAction.hpp"
#include "../BaseSlider.hpp"
#include <cmath>

namespace ie {
	SliderAction::SliderAction(sf::Vector2i division) :
		slider(nullptr), startMousePosition(), startValue(), division(division) {
	}
	
	void SliderAction::init(BasicActionInitInfo<BaseSlider&> initInfo) {
		slider = &initInfo.additional;
	}
	
	sf::Vector2f SliderAction::getMousePosition() {
		return sf::Vector2f{mousePosition};
	}
	
	void SliderAction::startPressed() {
		if(!slider->onSlider(mousePosition)) {
			slider->setValueByMouse(mousePosition);
		}
		startValue = slider->getValue();
		startMousePosition = mousePosition;
	}
	
	void SliderAction::stopPressed() {
	}
	
	void SliderAction::whilePressed() {
		sf::Vector2f mouseOffset{sf::Vector2i{mousePosition.x - startMousePosition.x, mousePosition.y - startMousePosition.y}};
		sf::Vector2f newValue;
		newValue = slider->moveSlider(startValue, mouseOffset);
		newValue = BaseSlider::roundValueToDivision(newValue, division);
		slider->setValue(newValue);
	}
	
	void SliderAction::whileNotPressed() {
	}
	
	void SliderAction::setSlider(BaseSlider& slider) {
		this->slider = &slider;
	}
	
	SliderAction* SliderAction::copy() {
		return new SliderAction{*this};
	}
}
