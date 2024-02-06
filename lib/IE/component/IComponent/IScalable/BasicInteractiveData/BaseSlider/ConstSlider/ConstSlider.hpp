#pragma once

#include "../BaseSlider.hpp"

namespace ie {
	class ConstSlider : public BaseSlider {
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<INonInteractive::Make> slider;
			BoxPtr<INonInteractive::Make> background;
			MakeDyn<ISMRVec2F> value;
			sf::Vector2i division;
			float slider_scale;
			Key key;
			bool wheel_horizontal;
			SliderWheelAction::Relativity wheel_relativity;
			sf::Vector2f wheel_sensitivity;
			
			Make(
				BoxPtr<INonInteractive::Make>&& slider,
				BoxPtr<INonInteractive::Make>&& background,
				MakeDyn<ISMRVec2F> value,
				float slider_scale = 1.0f,
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false,
				SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationArea,
				sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
			);
			
			Make(
				BoxPtr<INonInteractive::Make>&& slider,
				BoxPtr<INonInteractive::Make>&& background,
				MakeDyn<ISMRVec2F> value,
				sf::Vector2i division,
				float slider_scale = 1.0f,
				Key key = Key::MouseLeft,
				bool wheel_horizontal = false
			);
			
			ConstSlider* make(InitInfo init_info) override;
		};
		
		ConstSlider(Make&& make, InitInfo init_info);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
	protected:
		float aspect_ratio_;
		float slider_scale_;
	};
}

template<>
struct ieml::Decode<char, ie::ConstSlider::Make> {
	static orl::Option<ie::ConstSlider::Make> decode(ieml::Node const& node);
};
