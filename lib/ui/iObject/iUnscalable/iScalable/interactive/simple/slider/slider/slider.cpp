#include "slider.hpp"

ui::Slider::Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2f sliderScale, sf::Mouse::Button button, bool wheelHorizontal, ui::SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
	BaseSlider(slider, background, value, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), scale(sliderScale) {}

ui::Slider::Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2i division, sf::Vector2f sliderScale, sf::Mouse::Button button, bool wheelHorizontal) :
	BaseSlider(slider, background, value, new SliderInteraction{*this, button, division, wheelHorizontal}), scale(sliderScale) {}

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

ui::Slider::Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, SliderInteraction *interaction, sf::Vector2f sliderScale) :
	BaseSlider(slider, background, value, interaction), scale(sliderScale) {}

ui::Slider *ui::Slider::copy() {
	Slider* slider1 {new Slider{slider->copy(), background->copy(), value, dynamic_cast<SliderInteraction*>(interaction->copy()), scale}};
	dynamic_cast<SliderInteraction*>(slider1->interaction)->setSlider(*slider1);
	BaseSlider::copy(slider1);
	return slider1;
}

ui::Slider *ui::Slider::createFromYaml(const YAML::Node &node) {
	ui::IUninteractive *slider;
	ui::IUninteractive *background;
	std::shared_ptr<WithCoefficientVec2> value;
	sf::Vector2f sliderScale{1.0f, 0.5f};
	sf::Mouse::Button button{sf::Mouse::Left};
	bool wheelHorizontal{false};
	
	node["slider"] >> slider;
	node["background"] >> background;
	value = ui::Buffer::getObject<WithCoefficientVec2>(node["value"]);
	if(node["slider-scale"])
		node["slider-scale"] >> sliderScale;
	if(node["button"])
		node["button"] >> button;
	if(node["default-wheel"]) {
		wheelHorizontal = createBoolFromYaml(node["default-wheel"], "horizontal", "vertical");
	}
	
	if(!node["division"]) {
		SliderWheelEvent::Relativity wheelRelativity{SliderWheelEvent::Relativity::relationArea};
		sf::Vector2f wheelSensitivity{0.2f, 0.2f};
		
		if(node["wheel-relativity"])
			wheelRelativity = SliderWheelEvent::createRelativityFromYaml(node["wheel-relativity"]);
		if(node["wheel-sensitivity"])
			node["wheel-sensitivity"] >> wheelSensitivity;
		
		return new Slider{slider, background, value, sliderScale, button, wheelHorizontal, wheelRelativity, wheelSensitivity};
		return nullptr;
	} else {
		sf::Vector2i division;
		
		node["division"] >> division;
		
		return new Slider{slider, background, value, division, sliderScale, button, wheelHorizontal};
		return nullptr;
	}
}
