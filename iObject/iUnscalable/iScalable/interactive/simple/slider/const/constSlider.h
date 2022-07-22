#pragma once
#include "../baseSlider.h"

namespace ui {
	class ConstSlider : public BaseSlider {
	protected:
		float aspectRatio;
		float sliderScale;
		
		ConstSlider(ui::IDrawable *slider, ui::IDrawable *background, SliderInteraction *interaction);
		
	public:
		ConstSlider(ui::IDrawable *slider, ui::IDrawable *background, float sliderScale = 1.0f, sf::Mouse::Button button = sf::Mouse::Left,
					bool wheelHorizontal = false, SliderWheelEvent::Sensitivity wheelRelativity = SliderWheelEvent::Sensitivity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		ConstSlider(ui::IDrawable *slider, ui::IDrawable *background, sf::Vector2i division, float sliderScale = 1.0f, sf::Mouse::Button button = sf::Mouse::Left, bool wheelHorizontal = false);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ConstSlider* copy() override;
	};
}
