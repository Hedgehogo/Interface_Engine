#pragma once
#include "../baseSlider.hpp"

namespace ui {
	class ConstSlider : public BaseSlider {
	protected:
		float aspectRatio;
		float sliderScale;
		
		ConstSlider(ui::OnlyDrawable *slider, ui::OnlyDrawable *background, SliderInteraction *interaction);
		
	public:
		ConstSlider(ui::OnlyDrawable *slider, ui::OnlyDrawable *background, float sliderScale = 1.0f, sf::Mouse::Button button = sf::Mouse::Left,
					bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		ConstSlider(ui::OnlyDrawable *slider, ui::OnlyDrawable *background, sf::Vector2i division, float sliderScale = 1.0f, sf::Mouse::Button button = sf::Mouse::Left, bool wheelHorizontal = false);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ConstSlider* copy() override;
		
		static ConstSlider* createFromYaml(const YAML::Node &node);
	};
}
