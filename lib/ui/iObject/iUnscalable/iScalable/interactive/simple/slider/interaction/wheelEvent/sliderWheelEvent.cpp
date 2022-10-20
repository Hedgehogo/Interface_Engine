#include "sliderWheelEvent.hpp"
#include "../../baseSlider.hpp"

namespace ui {
	SliderWheelEvent::SliderWheelEvent(BaseSlider &slider, bool horizontal, Relativity relativity, sf::Vector2f sensitivity) :
		slider(&slider), sensitivity(sensitivity), horizontal(horizontal), relativity(relativity == Relativity::relationSlider) {
	}
	
	void SliderWheelEvent::startPressed(sf::Vector2i, int) {}
	
	void SliderWheelEvent::stopPressed(sf::Vector2i, int) {}
	
	void SliderWheelEvent::whilePressed(sf::Vector2i, int value) {
		sf::Vector2f move{sensitivity};
		if(relativity) {
			sf::Vector2f sliderSize{slider->getSliderSize()};
			sf::Vector2f areaSize{slider->getSliderSize()};
			move = {sliderSize.x / areaSize.x * move.x, sliderSize.y / areaSize.y * move.y};
		}
		move *= -static_cast<float>(value);
		if((isKeyPressed(Key::lShift) || isKeyPressed(Key::rShift)) != horizontal) {
			move.y = 0;
		} else {
			move.x = 0;
		}
		slider->setValue(slider->getValue() + move);
	}
	
	void SliderWheelEvent::whileNotPressed(sf::Vector2i, int) {}
	
	void SliderWheelEvent::setSlider(BaseSlider &slider) {
		this->slider = &slider;
	}
	
	SliderWheelEvent *SliderWheelEvent::copy() {
		SliderWheelEvent *sliderWheelEvent{new SliderWheelEvent{*slider, horizontal, (relativity ? Relativity::relationSlider : Relativity::relationArea), sensitivity}};
		WheelEvent::copy(sliderWheelEvent);
		return sliderWheelEvent;
	}
	
	template <>
	bool convert(const YAML::Node &node, SliderWheelEvent::Relativity &relativity) {
		if(convertBool(node, "relationArea", "relationSlider")) {
			relativity = SliderWheelEvent::Relativity::relationArea;
		} else {
			relativity = SliderWheelEvent::Relativity::relationSlider;
		}
		return true;
	}
}
