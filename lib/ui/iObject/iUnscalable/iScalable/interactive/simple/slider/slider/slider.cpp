#include "slider.hpp"

namespace ui {
	Slider::Slider(
		IUninteractive* slider, IUninteractive* background, const PSRVec2f& value, sf::Vector2f sliderScale, Key key, bool wheelHorizontal, SliderWheelEvent::Relativity wheelRelativity,
		sf::Vector2f wheelSensitivity
	) : BaseSlider(slider, background, value, new SliderInteraction{*this, key, wheelHorizontal, wheelRelativity, wheelSensitivity}), scale(sliderScale) {
	}
	
	Slider::Slider(IUninteractive* slider, IUninteractive* background, const PSRVec2f& value, sf::Vector2i division, sf::Vector2f sliderScale, Key key, bool wheelHorizontal) :
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
	
	sf::Vector2f Slider::getMinSize() const {
		sf::Vector2f minSize{slider->getMinSize()};
		minSize = {minSize.x / scale.x, minSize.y / scale.y};
		return minSize;
	}
	
	Slider::Slider(IUninteractive* slider, IUninteractive* background, const PSRVec2f& value, SliderInteraction* interaction, sf::Vector2f sliderScale) :
		BaseSlider(slider, background, value, interaction), scale(sliderScale) {
	}
	
	Slider* Slider::copy() {
		Slider* slider1{new Slider{slider->copy(), background->copy(), value, dynamic_cast<SliderInteraction*>(interaction->copy()), scale}};
		dynamic_cast<SliderInteraction*>(slider1->interaction)->setSlider(*slider1);
		BaseSlider::copy(slider1);
		return slider1;
	}
	
	bool DecodePointer<Slider>::decodePointer(const YAML::Node& node, Slider*& sliderZone) {
		auto slider{node["slider"].as<IUninteractive*>()};
		auto background{node["background"].as<IUninteractive*>()};
		auto value{Buffer::get<SRVec2f>(node["value"])};
		auto sliderScale{convDef(node["slider-scale"], sf::Vector2f{1.0f, 0.5f})};
		auto key{convDef(node["key"], Key::mouseLeft)};
		auto wheelHorizontal{convBoolDef(node["default-wheel"], "horizontal", "vertical", false)};
		
		if(!node["division"]) {
			auto wheelRelativity{convDef(node["wheel-relativity"], SliderWheelEvent::Relativity::relationArea)};
			auto wheelSensitivity{convDef(node["wheel-sensitivity"], sf::Vector2f{0.2f, 0.2f})};
			
			sliderZone = new Slider{slider, background, value, sliderScale, key, wheelHorizontal, wheelRelativity, wheelSensitivity};
		} else {
			auto division{node["division"].as<sf::Vector2i>()};
			
			sliderZone = new Slider{slider, background, value, division, sliderScale, key, wheelHorizontal};
		}
		return true;
	}
}
