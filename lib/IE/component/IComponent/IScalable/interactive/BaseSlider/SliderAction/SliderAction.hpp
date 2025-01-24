#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/trigger/IAction/IBasicTouchAction/IBasicTouchAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public virtual IBasicTouchAction<BaseSlider&> {
	public:
		struct Make : public virtual IBasicTouchAction<BaseSlider&>::Make {
			sf::Vector2i division = {0, 0};
			
			Make(sf::Vector2i division = {0, 0});
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderAction* override;
		};
		
		SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto set_slider(BaseSlider& slider) -> void;
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		bool active;
		ActiveTracker tracker_;
		BaseSlider* slider_;
		sf::Vector2i start_touch_position_;
		sf::Vector2f start_value_;
		sf::Vector2i division_;
	};
}