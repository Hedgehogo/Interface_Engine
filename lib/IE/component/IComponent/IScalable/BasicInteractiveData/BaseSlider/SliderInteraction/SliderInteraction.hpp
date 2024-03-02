#pragma once

#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/interaction/IInteraction/BasicPressedInteraction/BasicPressedInteraction.hpp"
#include "IE/component/IComponent/IScalable/BasicInteractiveData/BaseSlider/SliderAction/SliderAction.hpp"
#include "../SliderWheelAction/SliderWheelAction.hpp"

namespace ie {
	class SliderInteraction : public BasicOneKeyInteraction<BaseSlider&> {
	public:
		struct Make : public virtual IBasicInteraction<BaseSlider&>::Make {
			Key key;
			sf::Vector2i division;
			bool wheel_horizontal;
			SliderWheelAction::Relativity wheel_relativity;
			sf::Vector2f wheel_sensitivity;
			
			Make(Key key, sf::Vector2i division, bool wheel_horizontal, SliderWheelAction::Relativity wheel_relativity, sf::Vector2f wheel_sensitivity);
			
			Make(
				Key key,
				bool wheel_horizontal = false,
				SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationSlider,
				sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
			);
			
			Make(Key key, sf::Vector2i division = {10, 10}, bool wheel_horizontal = false);
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderInteraction* override;
		};
		
		SliderInteraction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto set_slider(BaseSlider& slider) -> void;
		
		auto update(sf::Vector2i mouse_position) -> void override;
		
	protected:
		SliderWheelAction wheel_action_;
	};
}