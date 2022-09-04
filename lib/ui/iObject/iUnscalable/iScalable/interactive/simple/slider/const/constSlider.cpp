#include <iostream>
#include "constSlider.hpp"

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal,
                             ui::SliderWheelEvent::Relativity wheelRelativity, sf::Vector2f wheelSensitivity) :
	BaseSlider(slider, background, value, new SliderInteraction{*this, button, wheelHorizontal, wheelRelativity, wheelSensitivity}), sliderScale(sliderScale) {
	
	sliderSize = slider->getNormalSize();
	aspectRatio = sliderSize.x / sliderSize.y;
}

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2i division, float sliderScale, sf::Mouse::Button button, bool wheelHorizontal) :
	BaseSlider(slider, background, value, new SliderInteraction{*this, button, division, wheelHorizontal}), sliderScale(sliderScale) {
	
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

ui::ConstSlider::ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, ui::SliderInteraction *interaction) :
	BaseSlider(slider, background, value, interaction) {}

ui::ConstSlider* ui::ConstSlider::copy() {
	ConstSlider* constSlider {new ConstSlider{slider->copy(), background->copy(), value, dynamic_cast<SliderInteraction*>(interaction->copy())}};
	dynamic_cast<SliderInteraction*>(constSlider->interaction)->setSlider(*constSlider);
	BaseSlider::copy(constSlider);
	return constSlider;
}

ui::ConstSlider *ui::ConstSlider::createFromYaml(const YAML::Node &node) {
	ui::IUninteractive *slider;
	ui::IUninteractive *background;
	std::shared_ptr<WithCoefficientVec2> value;
	float sliderScale{1.0f};
	sf::Mouse::Button button{sf::Mouse::Left};
	bool wheelHorizontal{false};
	
	node["slider"] >> slider;
	node["background"] >> background;
	value = ui::Buffer::get<WithCoefficientVec2>(node["value"]);
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
		
		return new ConstSlider{slider, background, value, sliderScale, button, wheelHorizontal, wheelRelativity, wheelSensitivity};
		return nullptr;
	} else {
		sf::Vector2i division;
		
		node["division"] >> division;
		
		return new ConstSlider{slider, background, value, division, sliderScale, button, wheelHorizontal};
		return nullptr;
	}
}
