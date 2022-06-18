#pragma once
#include "../baseSlider.h"

namespace ui {
	class Slider : public BaseSlider {
	protected:
		sf::Vector2f scale;
		
		Slider(ui::IDrawn *slider, ui::IDrawn *background, SliderInteraction *interaction, sf::Vector2f sliderScale);
	
	public:
		Slider(ui::IDrawn *slider, ui::IDrawn *background, sf::Vector2f sliderScale = {1.0f, 0.5f}, sf::Mouse::Button button = sf::Mouse::Left,
			bool wheelHorizontal = false, SliderWheelEvent::Sensitivity wheelRelativity = SliderWheelEvent::Sensitivity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		Slider(ui::IDrawn *slider, ui::IDrawn *background, sf::Vector2i division, sf::Vector2f sliderScale = {1.0f, 0.5f}, sf::Mouse::Button button = sf::Mouse::Left, bool wheelHorizontal = false);
		
		void setScale(sf::Vector2f scale);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		Slider* copy() override;
	};
}
