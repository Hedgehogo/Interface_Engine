#include "slider.hpp"

namespace ui {
	Slider::Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f &value, sf::Vector2f sliderScale, Key key, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity,
				   sf::Vector2f wheelSensitivity) :
		BaseSlider(slider, background, value, new SliderInteraction{*this, key, wheelHorizontal, wheelRelativity, wheelSensitivity}), scale(sliderScale) {
	}
	
	Slider::Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f &value, sf::Vector2i division, sf::Vector2f sliderScale, Key key, bool wheelHorizontal) :
		BaseSlider(slider, background, value, new SliderInteraction{*this, key, division, wheelHorizontal}), scale(sliderScale) {
	}
	
	void Slider::setScale(sf::Vector2f scale) {
		this->scale = scale;
	}
	
	void Slider::resize(sf::Vector2f size, sf::Vector2f position) {
		this->position = position;
		sliderSize = {size.x * scale.x, size.y * scale.y};
		moveZoneSize = size - sliderSize;
		background->resize(size, position);
		resizeSlider(value->getValue());
	}
	
	sf::Vector2f Slider::getMinSize() {
		sf::Vector2f minSize{slider->getMinSize()};
		minSize = {minSize.x / scale.x, minSize.y / scale.y};
		return minSize;
	}
	
	Slider::Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f &value, SliderInteraction *interaction, sf::Vector2f sliderScale) :
		BaseSlider(slider, background, value, interaction), scale(sliderScale) {
	}
	
	Slider *Slider::copy() {
		Slider *slider1{new Slider{slider->copy(), background->copy(), value, dynamic_cast<SliderInteraction *>(interaction->copy()), scale}};
		dynamic_cast<SliderInteraction *>(slider1->interaction)->setSlider(*slider1);
		BaseSlider::copy(slider1);
		return slider1;
	}
	
	bool convertPointer(const YAML::Node &node, Slider *&sliderZone) {
		IUninteractive *slider;
		IUninteractive *background;
		PSRVec2f value;
		sf::Vector2f sliderScale{1.0f, 0.5f};
		Key key{Key::mouseLeft};
		bool wheelHorizontal{false};
		
		node["slider"] >> slider;
		node["background"] >> background;
		value = Buffer::get<SRVec2f>(node["value"]);
		if(node["slider-scale"])
			node["slider-scale"] >> sliderScale;
		if(node["key"])
			node["key"] >> key;
		if(node["default-wheel"]) {
			wheelHorizontal = convertBool(node["default-wheel"], "horizontal", "vertical");
		}
		
		if(!node["division"]) {
			SliderWheelEvent::Relativity wheelRelativity{SliderWheelEvent::Relativity::relationArea};
			sf::Vector2f wheelSensitivity{0.2f, 0.2f};
			
			if(node["wheel-relativity"])
				node["wheel-relativity"] >> wheelRelativity;
			if(node["wheel-sensitivity"])
				node["wheel-sensitivity"] >> wheelSensitivity;
			
			{ sliderZone = new Slider{slider, background, value, sliderScale, key, wheelHorizontal, wheelRelativity, wheelSensitivity}; return true; }
		} else {
			sf::Vector2i division;
			
			node["division"] >> division;
			
			{ sliderZone = new Slider{slider, background, value, division, sliderScale, key, wheelHorizontal}; return true; }
		}
	}
	
	bool DecodePointer<Slider>::decodePointer(const YAML::Node &node, Slider *&sliderZone) {
		IUninteractive *slider;
		IUninteractive *background;
		PSRVec2f value;
		sf::Vector2f sliderScale{1.0f, 0.5f};
		Key key{Key::mouseLeft};
		bool wheelHorizontal{false};
		
		node["slider"] >> slider;
		node["background"] >> background;
		value = Buffer::get<SRVec2f>(node["value"]);
		if(node["slider-scale"])
			node["slider-scale"] >> sliderScale;
		if(node["key"])
			node["key"] >> key;
		if(node["default-wheel"]) {
			wheelHorizontal = convertBool(node["default-wheel"], "horizontal", "vertical");
		}
		
		if(!node["division"]) {
			SliderWheelEvent::Relativity wheelRelativity{SliderWheelEvent::Relativity::relationArea};
			sf::Vector2f wheelSensitivity{0.2f, 0.2f};
			
			if(node["wheel-relativity"])
				node["wheel-relativity"] >> wheelRelativity;
			if(node["wheel-sensitivity"])
				node["wheel-sensitivity"] >> wheelSensitivity;
			
			{ sliderZone = new Slider{slider, background, value, sliderScale, key, wheelHorizontal, wheelRelativity, wheelSensitivity}; return true; }
		} else {
			sf::Vector2i division;
			
			node["division"] >> division;
			
			{ sliderZone = new Slider{slider, background, value, division, sliderScale, key, wheelHorizontal}; return true; }
		}
	}
}
