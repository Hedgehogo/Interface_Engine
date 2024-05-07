#pragma once

#include "IE/interaction/IAction/BasicTouchAction/BasicBaseTouchAction/BasicBaseTouchAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public BasicBaseTouchAction<BaseSlider&> {
	public:
		struct Make : public BasicTouchAction<BaseSlider&>::Make {
			sf::Vector2i division = {0, 0};
			
			Make(sf::Vector2i division = {0, 0});
			
			auto make(BasicActionInitInfo<BaseSlider&> init_info) -> SliderAction* override;
		};
		
		SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		auto set_slider(BaseSlider& slider) -> void;
		
	protected:
		auto get_mouse_position() -> sf::Vector2f;
		
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		BaseSlider* slider_;
		sf::Vector2i start_mouse_position_;
		sf::Vector2f start_value_;
		sf::Vector2i division_;
	};
}