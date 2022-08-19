#include <iostream>
#include "constSlider.hpp"

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal,
                             ui::SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
	BaseSlider(slider, background, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), sliderScale(sliderScale) {
	
	sliderSize = slider->getNormalSize();
	aspectRatio = sliderSize.x / sliderSize.y;
}

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, sf::Vector2i division, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal) :
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

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, ui::SliderInteraction *interaction) :
	BaseSlider(slider, background, interaction) {}

ui::ConstSlider* ui::ConstSlider::copy() {
	ConstSlider* constSlider {new ConstSlider{slider->copy(), background->copy(), dynamic_cast<SliderInteraction*>(interaction->copy())}};
	dynamic_cast<SliderInteraction*>(constSlider->interaction)->setSlider(*constSlider);
	BaseSlider::copy(constSlider);
	return constSlider;
}

ui::ConstSlider *ui::ConstSlider::createFromYaml(const YAML::Node &node) {
	ui::IUninteractive *slider;
	ui::IUninteractive *background;
	float sliderScale{1.0f};
	sf::Mouse::Button button{sf::Mouse::Left};
	bool wheelHorizontal{false};
	
	node["slider"] >> slider;
	node["background"] >> background;
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
		
		return new ConstSlider{slider, background, sliderScale, button, wheelHorizontal, wheelRelativity, wheelSensitivity};
	} else {
		sf::Vector2i division;
		
		node["division"] >> division;
		
		return new ConstSlider{slider, background, division, sliderScale, button, wheelHorizontal};
	}
}
