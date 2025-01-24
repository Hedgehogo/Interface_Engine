#pragma once

#include "IE/trigger/ITrigger/BasicTouchTrigger/BasicTouchTrigger.hpp"
#include "IE/trigger/ITrigger/BasicActiveTrigger/BasicActiveTrigger.hpp"
#include "IE/component/IComponent/IScalable/interactive/BaseSlider/SliderAction/SliderAction.hpp"
#include "../SliderWheelAction/SliderWheelAction.hpp"

namespace ie {
	class SliderTrigger : public BasicActiveTrigger<BaseSlider&> {
	public:
		struct Make : public virtual IBasicTrigger<BaseSlider&>::Make {
			Key key;
			sf::Vector2i division;
			bool wheel_horizontal;
			SliderWheelAction::Relativity wheel_relativity;
			sf::Vector2f wheel_sensitivity;
			
			Make(
				Key key,
				sf::Vector2i division,
				bool wheel_horizontal,
				SliderWheelAction::Relativity wheel_relativity,
				sf::Vector2f wheel_sensitivity
			);
			
			Make(
				Key key,
				bool wheel_horizontal = false,
				SliderWheelAction::Relativity wheel_relativity = SliderWheelAction::Relativity::RelationSlider,
				sf::Vector2f wheel_sensitivity = {0.2f, 0.2f}
			);
			
			Make(Key key, sf::Vector2i division = {10, 10}, bool wheel_horizontal = false);
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderTrigger* override;
		};
		
		SliderTrigger(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
	
	protected:
		SliderWheelAction wheel_action_;
		float delta_;
	};
}
