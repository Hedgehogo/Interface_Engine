#pragma once
#include "../baseSlider.hpp"

namespace ui {
	class Slider : public BaseSlider {
	protected:
		sf::Vector2f scale;
		
		Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, SliderInteraction *interaction, sf::Vector2f sliderScale);
	
	public:
		Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2f sliderScale = {1.0f, 0.5f}, sf::Mouse::Button button = sf::Mouse::Left,
               bool wheelHorizontal = false, SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea, sf::Vector2f wheelSensitivity = {0.2f, 0.2f});
		
		Slider(ui::IUninteractive *slider, ui::IUninteractive *background, const std::shared_ptr<WithCoefficientVec2>& value, sf::Vector2i division, sf::Vector2f sliderScale = {1.0f, 0.5f}, sf::Mouse::Button button = sf::Mouse::Left, bool wheelHorizontal = false);
		
		void setScale(sf::Vector2f scale);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		Slider* copy() override;
		
		static Slider* createFromYaml(const YAML::Node &node);
	};
}
