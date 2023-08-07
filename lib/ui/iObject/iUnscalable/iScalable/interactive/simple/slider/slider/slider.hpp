#pragma once

#include "../baseSlider.hpp"

namespace ui {
	class Slider : public BaseSlider {
	public:
		struct Make : public IScalable::Make {
			BoxPtr<IUninteractive::Make> slider;
			BoxPtr<IUninteractive::Make> background;
			const PSRVec2f& value;
			sf::Vector2i division;
			sf::Vector2f sliderScale;
			Key key;
			bool wheelHorizontal;
			SliderWheelEvent::Relativity wheelRelativity;
			sf::Vector2f wheelSensitivity;
			
			Make(
				BoxPtr<IUninteractive::Make>&& slider,
				BoxPtr<IUninteractive::Make>&& background,
				const PSRVec2f& value,
				sf::Vector2f sliderScale = {1.0f, 0.5f},
				Key key = Key::mouseLeft,
				bool wheelHorizontal = false,
				SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea,
				sf::Vector2f wheelSensitivity = {0.2f, 0.2f}
			);
			
			Make(
				BoxPtr<IUninteractive::Make>&& slider,
				BoxPtr<IUninteractive::Make>&& background,
				const PSRVec2f& value,
				sf::Vector2i division,
				sf::Vector2f sliderScale = {1.0f, 0.5f},
				Key key = Key::mouseLeft,
				bool wheelHorizontal = false
			);
			
			Slider* make(InitInfo initInfo) override;
		};
		
		Slider(Make&& make, InitInfo initInfo);
		
		Slider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			sf::Vector2f sliderScale = {1.0f, 0.5f},
			Key key = Key::mouseLeft,
			bool wheelHorizontal = false,
			SliderWheelEvent::Relativity wheelRelativity = SliderWheelEvent::Relativity::relationArea,
			sf::Vector2f wheelSensitivity = {0.2f, 0.2f}
		);
		
		Slider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			sf::Vector2i division,
			sf::Vector2f sliderScale = {1.0f, 0.5f},
			Key key = Key::mouseLeft,
			bool wheelHorizontal = false
		);
		
		void setScale(sf::Vector2f scale);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		Slider* copy() override;
	
	protected:
		sf::Vector2f scale;
	};
	
	template<>
	struct DecodePointer<Slider> {
		static bool decodePointer(const YAML::Node& node, Slider*& slider);
	};
}
