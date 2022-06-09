#include <iostream>
#include "constSlider.h"

ui::ConstSlider::ConstSlider(ui::IDrawn *slider, ui::IDrawn *background, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal, ui::SliderWheelEvent::Sensitivity wheelRelativity, sf::Vector2f wheelSensitivity) :
	BaseSlider(slider, background, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), sliderScale(sliderScale) {
	
	sliderSize = slider->getNormalSize();
	aspectRatio = sliderSize.x / sliderSize.y;
}

ui::ConstSlider::ConstSlider(ui::IDrawn *slider, ui::IDrawn *background, sf::Vector2i division, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal) :
	BaseSlider(slider, background, new SliderInteraction{*this, button, division, wheelHorizontal}), sliderScale(sliderScale) {
	
	sliderSize = slider->getNormalSize();
	aspectRatio = sliderSize.x / sliderSize.y;
}

void ui::ConstSlider::resize(sf::Vector2f size, sf::Vector2f position) {
	this->position = position;
	if(size.x / aspectRatio < size.y) {
		sliderSize = sf::Vector2f{size.x, size.x / aspectRatio} * sliderScale;
	} else {
		sliderSize = sf::Vector2f{size.y * aspectRatio, size.y} * sliderScale;
	}
	moveZoneSize = size - sliderSize;
	background->resize(size, position);
}
