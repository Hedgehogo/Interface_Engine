#pragma once
#include "../baseSlider.hpp"

namespace ui {
	class Slider : public BaseSlider {
	protected:
		sf::Vector2f scale;
		
		Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f& value, SliderInteraction *interaction, sf::Vector2f sliderScale);
	
	public:
		Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f& value, sf::Vector2f sliderScale = {1.0f, 0.5f}, Key key = Key::mouseLeft,
			   bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		Slider(IUninteractive *slider, IUninteractive *background, const PSRVec2f& value, sf::Vector2i division, sf::Vector2f sliderScale = {1.0f, 0.5f}, Key key = Key::mouseLeft, bool wheelHorizontal = false);
		
		void setScale(sf::Vector2f scale);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		Slider* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, Slider *&slider);
	
	template<>
	struct DecodePointer<Slider> {
		static bool decodePointer(const YAML::Node &node, Slider *&slider);
	};
}
