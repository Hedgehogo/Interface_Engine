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
			
			auto make(InitInfo init_info) -> ConstSlider* override;
		};
		
		ConstSlider(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
	protected:
		float aspect_ratio_;
		float slider_scale_;
	};
}

template<>
struct ieml::Decode<char, ie::ConstSlider::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ConstSlider::Make>;
};
