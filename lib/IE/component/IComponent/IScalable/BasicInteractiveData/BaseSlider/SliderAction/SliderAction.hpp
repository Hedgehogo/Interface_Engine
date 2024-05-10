#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/interaction/IAction/BasicTouchAction/BasicTouchAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public BasicTouchAction<BaseSlider&> {
	public:
		struct Make : public BasicTouchAction<BaseSlider&>::Make {
			sf::Vector2i division = {0, 0};
			
			Make(sf::Vector2i division = {0, 0});
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderAction* override;
		};
		
		SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto set_slider(BaseSlider& slider) -> void;
		
		auto update(sf::Vector2i point_position, bool active) -> void override;
		
	protected:
		ActiveTracker tracker_;
		BaseSlider* slider_;
		sf::Vector2i start_mouse_position_;
		sf::Vector2f start_value_;
		sf::Vector2i division_;
	};
}