#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public BasicBaseKeyAction<BaseSlider&> {
	public:
		struct Make : public BasicKeyAction<BaseSlider&>::Make {
			sf::Vector2i division = {0, 0};
			
			Make(sf::Vector2i division = {0, 0});
			
			SliderAction* make(BasicActionInitInfo<BaseSlider&> init_info) override;
		};
		
		SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> init_info);
		
		explicit SliderAction(sf::Vector2i division = {0, 0});
		
		void init(BasicActionInitInfo<BaseSlider&> init_info) override;
		
		void set_slider(BaseSlider& slider);
		
		SliderAction* copy() override;
	
	protected:
		sf::Vector2f get_mouse_position();
		
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		BaseSlider* slider;
		sf::Vector2i start_mouse_position;
		sf::Vector2f start_value;
		sf::Vector2i division;
	};
}