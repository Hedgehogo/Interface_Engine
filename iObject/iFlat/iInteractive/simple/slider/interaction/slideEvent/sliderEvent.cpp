#include "sliderEvent.h"
#include "../../baseSlider.h"
#include <cmath>

ui::SliderEvent::SliderEvent(BaseSlider &slider, sf::Vector2i division) :
	slider(slider), division(division), startMousePosition(), startValue() {}

void ui::SliderEvent::startPressed(sf::Vector2i windowPosition) {
	if(!slider.onSlider(windowPosition)) {
		slider.setValueByMouse(windowPosition);
	}
	startValue = slider.getValue();
	startMousePosition = windowPosition;
}

void ui::SliderEvent::stopPressed(sf::Vector2i) {}

void ui::SliderEvent::whilePressed(sf::Vector2i windowPosition) {
	sf::Vector2i mouseOffset{windowPosition.x - startMousePosition.x, windowPosition.y - startMousePosition.y};
	slider.setValue(startValue);
	slider.move(mouseOffset);
	slider.roundValueToDivision(division);
}

void ui::SliderEvent::notPressed(sf::Vector2i) {}
