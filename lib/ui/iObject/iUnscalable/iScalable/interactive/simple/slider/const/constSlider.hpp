#pragma once
#include "../baseSlider.hpp"

namespace ui {
	class ConstSlider : public BaseSlider {
	protected:
		float aspectRatio;
		float sliderScale;
		
		ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, SliderInteraction *interaction);
		
	public:
		ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, float sliderScale = 1.0f, Key button = Key::mouseLeft,
                    bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		ConstSlider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2i division, float sliderScale = 1.0f, Key button = Key::mouseLeft, bool wheelHorizontal = false);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ConstSlider* copy() override;
		
		static ConstSlider* createFromYaml(const YAML::Node &node);
	};
}
