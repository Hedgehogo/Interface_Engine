#include "slider.h"

ui::Slider::Slider(ui::IDrawn *slider, ui::IDrawn *background, sf::Vector2f sliderScale, sf::Mouse::Button button, bool wheelHorizontal, ui::SliderWheelEvent::Sensitivity wheelRelativity, sf::Vector2f wheelSensitivity) :
	BaseSlider(slider, background, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), scale(sliderScale) {}

ui::Slider::Slider(ui::IDrawn *slider, ui::IDrawn *background, sf::Vector2i division, sf::Vector2f sliderScale, sf::Mouse::Button button, bool wheelHorizontal) :
	BaseSlider(slider, background, new SliderInteraction{*this, button, division, wheelHorizontal}), scale(sliderScale) {}

void ui::Slider::setScale(sf::Vector2f scale) {
	this->scale = scale;
}

void ui::Slider::resize(sf::Vector2f size, sf::Vector2f position) {
	this->position = position;
	sliderSize = {size.x * scale.x, size.y * scale.y};
	moveZoneSize = size - sliderSize;
	background->resize(size, position);
}

sf::Vector2f ui::Slider::getMinSize() {
	sf::Vector2f minSize {slider->getMinSize()};
	minSize = {minSize.x / scale.x, minSize.y / scale.y};
	return minSize;
}
