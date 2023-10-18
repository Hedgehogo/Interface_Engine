#pragma once

#include "../BaseSlider.hpp"

namespace ie {
	class ConstSlider : public BaseSlider {
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<IUninteractive::Make> slider;
			BoxPtr<IUninteractive::Make> background;
			const PSRVec2f& value;
			sf::Vector2i division;
			float slider_scale;
			Key key;
			bool wheel_horizontal;
			SliderWheelAction::Relativity wheel_relativity;
			sf::Vector2f wheel_sensitivity;
			
			Make(
				BoxPtr<IUninteractive::Make>&& slider,
				BoxPtr<IUninteractive::Make>&& background,
				const PSRVec2f& value,
				float slider_scale = 1.0f,
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false,
				SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationArea,
				sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
			);
			
			Make(
				BoxPtr<IUninteractive::Make>&& slider,
				BoxPtr<IUninteractive::Make>&& background,
				const PSRVec2f& value,
				sf::Vector2i division,
				float slider_scale = 1.0f,
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false
			);
			
			ConstSlider* make(InitInfo init_info) override;
		};
		
		ConstSlider(Make&& make, InitInfo init_info);
		
		ConstSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			float slider_scale = 1.0f,
			Key key = Key::MouseLeft,
			bool wheel_horizontal = false,
			SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationArea,
			sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
		);
		
		ConstSlider(
			BoxPtr<IUninteractive>&& slider,
			BoxPtr<IUninteractive>&& background,
			const PSRVec2f& value,
			sf::Vector2i division,
			float slider_scale = 1.0f,
			Key key = Key::MouseLeft,
			bool wheel_horizontal = false
		);
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ConstSlider* copy() override;
	
	protected:
		float aspect_ratio;
		float slider_scale;
	};
	
	template<>
	struct DecodePointer<ConstSlider> {
		static bool decode_pointer(const YAML::Node& node, ConstSlider*& const_slider);
	};
}