#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"

namespace ie {
	class BaseSlider;
	
	class SliderAction : public BasicBaseKeyAction<BaseSlider&> {
	public:
		struct Make : public BasicKeyAction<BaseSlider&>::Make {
			sf::Vector2i division = {0, 0};
			
			Make(sf::Vector2i division = {0, 0});
			
			SliderAction* make(BasicActionInitInfo<BaseSlider&> initInfo) override;
		};
		
		SliderAction(Make&& make, BasicActionInitInfo<BaseSlider&> initInfo);
		
		explicit SliderAction(sf::Vector2i division = {0, 0});
		
		void init(BasicActionInitInfo<BaseSlider&> initInfo) override;
		
		void setSlider(BaseSlider& slider);
		
		SliderAction* copy() override;
	
	protected:
		sf::Vector2f getMousePosition();
		
		void startPressed() override;
		
		void stopPressed() override;
		
		void whilePressed() override;
		
		void whileNotPressed() override;
		
		BaseSlider* slider;
		sf::Vector2i startMousePosition;
		sf::Vector2f startValue;
		sf::Vector2i division;
	};
}